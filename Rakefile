require 'rake'
require 'rake/clean'
require 'tmpdir'

CFLAGS = "-Wall -Werror-implicit-function-declaration -std=c11 -Iinclude -Ivendor/gmp -Ivendor/mpfr/src -Ivendor/mpc/src -Ivendor/onigmo -Ivendor/judy/src -Ivendor/jemalloc/include/jemalloc -Ivendor/hash #{ENV['CFLAGS']}"

SOURCES      = FileList['source/**/*.c']
OBJECTS      = SOURCES.ext('o')
DEPENDENCIES = FileList[
	'vendor/gmp/.libs/libgmp.a',
	'vendor/mpfr/src/.libs/libmpfr.a',
	'vendor/mpc/src/.libs/libmpc.a',
	'vendor/onigmo/.libs/libonig.a',
	'vendor/judy/src/obj/.libs/libJudy.a',
	'vendor/jemalloc/lib/libjemalloc.a',
	'vendor/hash/hash.a'
]

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
	@FLAGS = %Q{CC=clang CFLAGS="-g0 -O3 -funroll-loops"}

	task :beard => ['libbeard.a', 'beard.h']

	task :gmp => 'submodules:gmp' do
		Dir.chdir 'vendor/gmp' do
			sh "./configure --enable-static --disable-shared #@FLAGS"
			sh 'make'
		end
	end

	task :mpfr => 'submodules:mpfr' do
		Dir.chdir 'vendor/mpfr' do
			sh "./configure --enable-static --disable-shared #@FLAGS"
			sh 'make'
		end
	end

	task :mpc => 'submodules:mpc' do
		Dir.chdir 'vendor/mpc' do
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

	task :hash => 'submodules:hash' do
		Dir.chdir 'vendor/hash' do
			sh 'rake build[release]'
		end
	end

	file 'libbeard.a' => DEPENDENCIES + OBJECTS do
		Dir.mktmpdir {|path|
			objects  = DEPENDENCIES.select { |p| p.end_with? '.o' }
			archives = DEPENDENCIES.select { |p| p.end_with? '.a' }

			archives.each {|name|
				real = File.realpath(name)

				FileUtils.mkpath "#{path}/#{File.basename(name)}"
				FileUtils.chdir "#{path}/#{File.basename(name)}" do
					sh "ar x #{real}"
				end
			}

			sh "ar rcs libbeard.a #{OBJECTS} #{objects} #{path}/*/**.o"
		}
	end

	file 'beard.h' => FileList['include/public/*.h'] do
		header  = File.read('include/public/common.h')
		header << File.read('include/public/magic.h').sub(/\A.*\*\/\n/m, '')

		%w[Value Runtime Integer String].each {|name|
			header << File.read("include/public/#{name}.h").sub(/\A.*\*\/\n/m, '')
		}

		File.open('beard.h', 'w') {|f|
			f.puts(header)
		}
	end

	file 'vendor/gmp/.libs/libgmp.a' do
		Rake::Task['build:gmp'].invoke
	end

	file 'vendor/mpfr/src/.libs/libmpfr.a' do
		Rake::Task['build:mpfr'].invoke
	end

	file 'vendor/mpc/src/.libs/libmpc.a' do
		Rake::Task['build:mpc'].invoke
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

	file 'vendor/hash/hash.a' do
		Rake::Task['build:hash'].invoke
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

	file 'test/run' => ['libbeard.a', 'beard.h', *files] do
		sh "clang #{CFLAGS} -Ivendor/tinytest -o test/run test/run.c vendor/tinytest/tinytest.c -pthread -ldl -L. -lbeard"
	end
end

namespace :submodules do
	task :fetch do
		sh 'git submodule init'
		sh 'git submodule update'
	end

	task :gmp      => 'vendor/gmp/configure'
	task :mpfr     => 'vendor/mpfr/configure'
	task :mpc      => 'vendor/mpc/configure'
	task :onigmo   => 'vendor/onigmo/configure.in'
	task :judy     => 'vendor/judy/configure'
	task :jemalloc => 'vendor/jemalloc/configure.ac'
	task :hash     => 'vendor/hash/Rakefile'
	task :tinytest => 'vendor/tinytest/tinytest.c'

	file 'vendor/gmp/configure' do
		Rake::Task['submodules:fetch'].invoke
	end

	file 'vendor/mpfr/configure' do
		Rake::Task['submodules:fetch'].invoke
	end

	file 'vendor/mpc/configure' do
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

	file 'vendor/hash/Rakefile' do
		Rake::Task['submodules:fetch'].invoke
	end

	file 'vendor/tinytest/tinytest.c' do
		Rake::Task['submodules:fetch'].invoke
	end
end

rule '.o' => '.c' do |t|
	sh "clang #{CFLAGS} -o #{t.name} -c #{t.source}"
end

rule '.h'

CLEAN.include(OBJECTS)

task :clobber do
	FileList['vendor/gmp', 'vendor/mpfr', 'vendor/mpc', 'vendor/onigmo', 'vendor/judy', 'vendor/jemalloc'].each {|dir|
		if File.directory? dir
			Dir.chdir dir do
				sh 'make distclean' rescue nil
			end
		end
	}

	Dir.chdir 'vendor/hash' do
		sh 'rake clobber'
	end
end

CLOBBER.include('libbeard.a', 'test/run', DEPENDENCIES)
