# Teapot v2.2.0 configuration generated at 2018-05-10 16:02:38 +1200

required_version "2.0"

# Project Metadata

define_project "coroutine" do |project|
	project.title = "Coroutine"
	project.license = 'MIT License'
	
	project.add_author 'Samuel Williams', email: 'samuel.williams@oriontransfer.co.nz'
	
	project.version = '0.1.0'
end

# Build Targets

define_target 'coroutine-library' do |target|
	target.build do
		source_root = target.package.path + 'source'
		copy headers: source_root.glob('Coroutine/**/*.{h,hpp}')
		build static_library: 'Coroutine', source_files: source_root.glob('Coroutine/**/*.{c,cpp}')
	end
	
	target.depends 'Build/Files'
	target.depends 'Build/Clang'
	
	target.depends :platform
	target.depends 'Language/C++14', private: true
	
	target.provides 'Library/Coroutine' do
		append linkflags [
			->{install_prefix + 'lib/libCoroutine.a'},
		]
	end
end

define_target 'coroutine-test' do |target|
	target.build do |*arguments|
		test_root = target.package.path + 'test'
		
		run tests: 'Coroutine', source_files: test_root.glob('Coroutine/**/*.cpp'), arguments: arguments
	end
	
	target.depends 'Library/UnitTest'
	target.depends 'Library/Coroutine'
	
	target.depends 'Language/C++14', private: true
	
	target.provides 'Test/Coroutine'
end

define_target 'coroutine-executable' do |target|
	target.build do
		source_root = target.package.path + 'source'
		
		build executable: 'Coroutine', source_files: source_root.glob('Coroutine.cpp')
	end
	
	target.depends 'Build/Files'
	target.depends 'Build/Clang'
	
	target.depends :platform
	target.depends 'Language/C++14', private: true
	
	target.depends 'Library/Coroutine'
	target.provides 'Executable/Coroutine'
end

define_target 'coroutine-run' do |target|
	target.build do |*arguments|
		run executable: 'Coroutine', arguments: arguments
	end
	
	target.depends 'Executable/Coroutine'
	target.provides 'Run/Coroutine'
end

# Configurations

define_configuration 'development' do |configuration|
	configuration[:source] = "https://github.com/kurocha/"
	configuration.import "coroutine"
	
	# Provides all the build related infrastructure:
	configuration.require 'platforms'
	
	# Provides unit testing infrastructure and generators:
	configuration.require 'unit-test'
	
	# Provides some useful C++ generators:
	configuration.require 'generate-cpp-class'
	
	configuration.require "generate-project"
	configuration.require "generate-travis"
end

define_configuration "coroutine" do |configuration|
	configuration.public!
end
