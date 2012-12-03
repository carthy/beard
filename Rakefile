require 'rake'
require 'rake/clean'
require 'tmpdir'

CC     = ENV['CC'] || 'clang'
AR     = ENV['AR'] || 'ar'
CFLAGS = "-std=c11 -Iinclude -Ivendor/gmp -Ivendor/onigmo -Ivendor/judy/src #{ENV['CFLAGS']}"

SOURCES      = FileList['source/**/*.c']
OBJECTS      = SOURCES.ext('o')
DEPENDENCIES = FileList['vendor/gmp/.libs/libgmp.a', 'vendor/onigmo/.libs/libonig.a', 'vendor/judy/src/obj/.libs/libJudy.a']

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
	task :beard => ['libbeard.a', 'beard.h']

	task :gmp => 'submodules:gmp' do
		Dir.chdir('vendor/gmp') do
			sh "./configure --enable-static --disable-shared CC=#{CC}"
			sh 'make'
		end
	end

	task :onigmo => 'submodules:onigmo' do
		Dir.chdir('vendor/onigmo') do
			sh "./configure --enable-static --disable-shared CC=#{CC}"
			sh 'make'
		end
	end

	task :judy => 'submodules:judy' do
		Dir.chdir('vendor/judy') do
			sh "./configure --enable-static --disable-shared CC=#{CC}"
			sh 'make'
		end
	end

	file 'libbeard.a' => DEPENDENCIES + OBJECTS do
		Dir.mktmpdir {|path|
			DEPENDENCIES.each {|name|
				real = File.realpath(name)

				FileUtils.mkpath "#{path}/#{File.basename(name)}"
				FileUtils.chdir "#{path}/#{File.basename(name)}" do
					sh "#{AR} x #{real}"
				end
			}

			sh "#{AR} rcs libbeard.a #{OBJECTS} #{path}/*/*.o"
		}
	end

	file 'beard.h' do
		header = ''

		FileList['include/public/{Value,GC,Integer}.h'].each {|f|
			header << File.read(f)
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
		sh "#{CC} #{CFLAGS} -Ivendor/tinytest -o test/run test/run.c vendor/tinytest/tinytest.c -static -L. -lbeard"
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

	file 'vendor/tinytest/tinytest.c' do
		Rake::Task['submodules:fetch'].invoke
	end
end

rule '.o' => '.c' do |t|
	sh "#{CC} #{CFLAGS} -o #{t.name} -c #{t.source}"
end

CLEAN.include(OBJECTS)

task :clobber do
	FileList['vendor/gmp', 'vendor/onigmo', 'vendor/judy'].each {|dir|
		if File.directory? dir
			Dir.chdir(dir) do
				sh 'make distclean' rescue nil
			end
		end
	}
end

CLOBBER.include('libbeard.a', 'test/run', DEPENDENCIES)
