require 'rake'
require 'rake/clean'
require 'tmpdir'

CC      = 'gcc'
AR      = 'ar'
CFLAGS  = '-std=gnu99 -Iinclude -Ivendor/gmp -Ivendor/onigmo'
LDFLAGS = '-lm -ldl -lpthread -lrt'

SOURCES      = FileList['source/**/*.c']
OBJECTS      = SOURCES.ext('o')
DEPENDENCIES = FileList['vendor/gmp/.libs/libgmp.a', 'vendor/onigmo/.libs/libonig.a']

CLEAN.include(OBJECTS)
CLOBBER.include('beard.so', 'beard-static.a', 'test/run', DEPENDENCIES)

task :default => :build

task :build, :mode do |t, args|
	mode = (args[:mode] || :debug).to_sym
  mode = :debug

	if mode == :debug
		CFLAGS << ' -O0 -g3'
	else
		CFLAGS << ' -Os -DNDEBUG'
	end

	Rake::Task['build:beard'].invoke
end

namespace :build do
	task :beard => ['beard.so', 'beard-static.a']

	task :gmp => 'submodules:gmp' do
		Dir.chdir 'vendor/gmp' do
			sh './configure --enable-static --disable-shared'
			sh 'make'
		end
	end

	task :onigmo => 'submodules:onigmo' do
		Dir.chdir 'vendor/onigmo' do
			sh 'make'
		end
	end

	file 'beard.so' => DEPENDENCIES + OBJECTS do
		sh "#{CC} #{CFLAGS} -fPIC #{OBJECTS} #{DEPENDENCIES} -shared -Wl,-soname,beard -o beard.so #{LDFLAGS}"
	end

	file 'beard-static.a' => DEPENDENCIES + OBJECTS do
		Dir.mktmpdir {|path|
			DEPENDENCIES.each {|name|
				real = File.realpath(name)

				FileUtils.mkpath "#{path}/#{File.basename(name)}"
				FileUtils.chdir "#{path}/#{File.basename(name)}" do
					sh "#{AR} x #{real}"
				end
			}

			sh "#{AR} rcs beard-static.a #{OBJECTS} #{path}/*/*.o"
		}
	end

	file 'vendor/gmp/.libs/libgmp.a' do
		Rake::Task['build:gmp'].invoke
	end

	file 'vendor/onigmo/.libs/libonig.a' do
		Rake::Task['build:onigmo'].invoke
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

	file 'test/run' => ['libtor-static.a', *files] do
		sh "#{CC} -std=gnu99 -Iinclude -Ivendor/tinytest -Ivendor/libuv/include -o test/run test/run.c vendor/tinytest/tinytest.c -L. -ltor-static #{LDFLAGS}"
	end
end

namespace :submodules do
	task :fetch do
		sh 'git submodule init'
		sh 'git submodule update'
	end

	task :gmp      => 'vendor/gmp/configure'
	task :onigmo   => 'vendor/onigmo/configure.in'
	task :tinytest => 'vendor/tinytest/tinytest.c'

	file 'vendor/gmp/configure' do
		Rake::Task['submodules:fetch'].invoke
	end

	file 'vendor/onigmo/configure' do
		Rake::Task['submodules:fetch'].invoke
	end

	file 'vendor/tinytest/tinytest.c' do
		Rake::Task['submodules:fetch'].invoke
	end
end

rule '.o' => '.c' do |t|
	sh "#{CC} -fPIC #{CFLAGS} -o #{t.name} -c #{t.source}"
end
