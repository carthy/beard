require 'rake'
require 'rake/clean'
require 'tmpdir'

CFLAGS = "-std=c11 -Iinclude -Ivendor/gmp -Ivendor/onigmo -Ivendor/judy/src -Ivendor/jemalloc/include/jemalloc -Ivendor/siphash #{ENV['CFLAGS']}"

SOURCES      = FileList['source/**/*.c']
OBJECTS      = SOURCES.ext('o')
DEPENDENCIES = FileList['vendor/gmp/.libs/libgmp.a', 'vendor/onigmo/.libs/libonig.a', 'vendor/judy/src/obj/.libs/libJudy.a', 'vendor/jemalloc/lib/libjemalloc.a', 'vendor/siphash/siphash.o']

task :default => :build

task :build, :mode do |t, args|
	mode = (args[:mode] || :debug).to_sym

	if mode == :debug
		CFLAGS << ' -O0 -g3'
	else
		CFLAGS << ' -Os -DNDEBUG'
	end

	Rake::Task['build:beard'].invoke
end

namespace :build do
	@FLAGS = 'CC=clang AR=llvm-ar RANLIB=llvm-ranlib CFLAGS="-emit-llvm -g0 -O3 -funroll-loops"'

	task :beard => ['beard.bc', 'beard.h']

	task :gmp => 'submodules:gmp' do
		Dir.chdir 'vendor/gmp' do
			sh "./configure --enable-static --disable-shared #@FLAGS"
			sh 'make'
		end
	end

	task :onigmo => 'submodules:onigmo' do
		Dir.chdir 'vendor/onigmo' do
			sh 'autoconf'
			sh "./configure --enable-static --disable-shared #@FLAGS"
			sh 'make'
		end
	end

	task :judy => 'submodules:judy' do
		Dir.chdir 'vendor/judy' do
			sh "./configure --enable-static --disable-shared #@FLAGS"
			sh 'make'
		end
	end

	task :jemalloc => 'submodules:jemalloc' do
		Dir.chdir 'vendor/jemalloc' do
			sh './autogen.sh'
			sh "./configure --enable-static --disable-shared --enable-lazy-lock #@FLAGS"
			sh 'make'
		end
	end

	task :siphash => 'submodules:siphash' do
		Dir.chdir 'vendor/siphash' do
			sh "clang #{CFLAGS} -emit-llvm -o siphash.o -c siphash.c"
		end
	end

	file 'beard.bc' => DEPENDENCIES + OBJECTS do
		sh "llvm-ld -export-dynamic -link-as-library -o beard.bc #{OBJECTS} #{DEPENDENCIES}"
	end

	file 'beard.h' => FileList['include/public/*.h'] do
		header = ''

		%w[Value Runtime Integer String].each {|name|
			header << File.read("include/public/#{name}.h")
		}

		File.open('beard.h', 'w') {|f|
			f.puts(header)
		}
	end

	file 'vendor/gmp/.libs/libgmp.a' do
		Rake::Task['build:gmp'].invoke
	end

	file 'vendor/onigmo/.libs/libonig.a' do
		Rake::Task['build:onigmo'].invoke
	end

	file 'vendor/judy/src/obj/.libs/libJudy.a' do
		Rake::Task['build:judy'].invoke
	end

	file 'vendor/jemalloc/lib/libjemalloc.a' do
		Rake::Task['build:jemalloc'].invoke
	end

	file 'vendor/siphash/siphash.o' do
		Rake::Task['build:siphash'].invoke
	end
end

task :test => 'test:run'

namespace :test do
	files = FileList['test/*.c'].each

	task :build => 'test/run'

	task :run => 'test:build' do
		sh 'test/run'
	end

	files.each {|path|
		file path
	}

	file 'test/run' => ['beard.bc', 'beard.h', *files] do
		sh "clang #{CFLAGS} -Ivendor/tinytest -o test/run beard.bc test/run.c vendor/tinytest/tinytest.c -pthread -ldl"
	end
end

namespace :submodules do
	task :fetch do
		sh 'git submodule init'
		sh 'git submodule update'
	end

	task :gmp      => 'vendor/gmp/configure'
	task :onigmo   => 'vendor/onigmo/configure.in'
	task :judy     => 'vendor/judy/configure'
	task :jemalloc => 'vendor/jemalloc/configure.ac'
	task :siphash  => 'vendor/siphash/siphash.h'
	task :tinytest => 'vendor/tinytest/tinytest.c'

	file 'vendor/gmp/configure' do
		Rake::Task['submodules:fetch'].invoke
	end

	file 'vendor/onigmo/configure' do
		Rake::Task['submodules:fetch'].invoke
	end

	file 'vendor/judy/configure' do
		Rake::Task['submodules:fetch'].invoke
	end

	file 'vendor/jemalloc/configure.ac' do
		Rake::Task['submodules:fetch'].invoke
	end

	file 'vendor/siphash/siphash.h' do
		Rake::Task['submodules:fetch'].invoke
	end

	file 'vendor/tinytest/tinytest.c' do
		Rake::Task['submodules:fetch'].invoke
	end
end

rule '.o' => '.c' do |t|
	sh "clang #{CFLAGS} -emit-llvm -o #{t.name} -c #{t.source}"
end

rule '.h'

CLEAN.include(OBJECTS)

task :clobber do
	FileList['vendor/gmp', 'vendor/onigmo', 'vendor/judy', 'vendor/jemalloc'].each {|dir|
		if File.directory? dir
			Dir.chdir dir do
				sh 'make distclean' rescue nil
			end
		end
	}

	Dir.chdir 'vendor/siphash' do
		sh 'rm -f siphash.o'
	end
end

CLOBBER.include('beard.bc', 'test/run', DEPENDENCIES)
