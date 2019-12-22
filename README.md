### NEELoader

```objective-c
/**
 * NEE_EXPORT_FUNCTION(usage, stage_key, args)
 *
 * @param USAGE 用户标识符
 * @param STAGE_KEY 执行标识符
 *
 * 例：
 *
 */
 
  NEE_EXPORT_FUNCTION(@"LaunchingItemA", @"Stage_key_A", NSArray *args) {
     arg1 = args.firstObject;
     NSLog(@"%@", arg1);
  }
 
/**
 * NEE_LOADER_EXECUTE(stage_key, arg1, agr2, ...)
 *
 * @param STAGE_KEY 执行标识符
 * @param ARG 入参
 *
 * 例:
 *
 */
  NEE_LOADER_EXECUTE(@"Stage_key_A", @"arg1");
 
 

 /**
 * NEE_EXPORT_ENV(@"AppID", @"12345678")
 *
 * @param key key
 * @param value value
 *
 */
  NEE_EXPORT_ENV(@"AppID", @"12345678");

 /**
 * NSString *appID = NEE_GET_ENV(@"AppID")
 *
 * @param key key
 * @return value
 *
 */
  NSString *appID = NEE_GET_ENV(@"AppID");

```