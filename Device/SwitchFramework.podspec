Pod::Spec.new do |s|
    s.name              = 'SwitchFramework'
    s.version           = '1.0.0'
    s.summary           = 'Kanvas Face Tracking'
    s.homepage          = 'http://getkanvas.com/'

    s.author            = { 'Name' => 'tony@getkanvas.com' }
    s.license           = { :type => 'proprietary', :file => 'LICENSE' }

    s.platform          = :ios
    s.source            = { :http => 'http://getkanvas.com' }

    s.ios.deployment_target = '8.0'

    s.frameworks = 'UIKit', 'SystemConfiguration', 'Security', 'SceneKit'
    s.vendored_frameworks = 'SwitchFramework.framework'
end
