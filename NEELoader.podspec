#
#  Be sure to run `pod spec lint WMH5SDK.podspec' to ensure this is a
#  valid spec and to remove all comments including this before submitting the spec.
#
#  To learn more about Podspec attributes see http://docs.cocoapods.org/specification.html
#  To see working Podspecs in the CocoaPods repo see https://github.com/CocoaPods/Specs/
#

Pod::Spec.new do |s|

  # ―――  Spec Metadata  ―――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #
  #
  #  These will help people to find your library, and whilst it
  #  can feel like a chore to fill in it's definitely to your advantage. The
  #  summary should be tweet-length, and the description more in depth.
  #

  s.name         = "NEELoader"
  s.version      = "1.0.0"
  s.summary      = "NEELoader"
  s.description  = "__Data段 数据注册与执行库"

  s.homepage     = "https://g.hz.netease.com/WM-iOS/NEELoader"
  s.license      = { :type => 'MIT', :file => 'LICENSE' }
  s.author             = { "fangxiaomin" => "fangxiaomin@corp.netease.com" }
  s.platform     = :ios, "7.0"

  s.source       = { :git => "https://g.hz.netease.com/WM-iOS/NEELoader.git", :tag => "#{s.version}" }
  s.source_files  = "NEELoader/*"

  s.requires_arc = true

end
