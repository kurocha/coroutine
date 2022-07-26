# Teapot v2.2.0 configuration generated at 2018-05-10 16:02:38 +1200

required_version "3.0"

# Project Metadata

define_project "coroutine" do |project|
	project.title = "Coroutine"
	project.license = 'MIT License'
	
	project.add_author 'Samuel Williams', email: 'samuel.williams@oriontransfer.co.nz'
	
	project.version = '0.1.0'
end

# Build Targets

define_target 'coroutine-test' do |target|
	target.depends 'Library/Time'
	target.depends 'Library/UnitTest'
	target.depends 'Library/Coroutine'
	
	target.depends 'Language/C++14', private: true
	
	target.provides 'Test/Coroutine' do |*arguments|
		test_root = target.package.path + 'test'
		
		run tests: 'Coroutine-tests', source_files: test_root.glob('Coroutine/**/*.cpp'), arguments: arguments
	end
end

# Configurations

define_configuration 'development' do |configuration|
	configuration[:source] = "https://github.com/kurocha/"
	configuration.import "coroutine"
	
	# Provides all the build related infrastructure:
	configuration.require 'platforms'
	
	# Provides unit testing infrastructure and generators:
	configuration.require 'unit-test'
	
	configuration.require 'time'
	
	# Provides some useful C++ generators:
	configuration.require 'generate-cpp-class'
	
	configuration.require "generate-project"
	configuration.require "generate-travis"
end

define_configuration "coroutine" do |configuration|
	configuration.public!
	
	host(/x86_64/) do
		configuration.require "coroutine-amd64"
	end

	host(/i386/) do
		configuration.require "coroutine-x86"
	end

	host(/win32/) do
		configuration.require "coroutine-win32"
	end
	
	host(/win64/) do
		configuration.require "coroutine-win64"
	end
	
	host(/arm32/) do
		configuration.require "coroutine-arm32"
	end
	
	host(/arm64/) do
		configuration.require "coroutine-arm64"
	end
end
