//
//  NEELoaderManager.m
//  SnailReader
//
//  Created by F_knight on 2019/4/15.
//  Copyright © 2019 com.netease. All rights reserved.
//

#import "NEELoaderManager.h"
#import "NEELoaderStore.h"
#import "NEELoaderAnnotation.h"
#import <mach-o/dyld.h>
#import <mach-o/getsect.h>
#import "NEELoaderManager+Log.h"
#import "NEELoaderEntry+Log.h"

@interface NEELoaderManager ()

@property (nonatomic, strong) NEELoaderStore *store;

@end

@implementation NEELoaderManager
+ (instancetype)shareInstance {
    static id _sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _sharedInstance = [[self alloc] init];
        [_sharedInstance readConfig];
    });
    
    return _sharedInstance;
}

- (instancetype)init {
    if (self = [super init]) {
        self.store = [[NEELoaderStore alloc] init];
    }
    return self;
}

- (void)readConfig {

#ifdef __LP64__
    typedef uint64_t nee_value;
    typedef struct section_64 nee_section;
    typedef struct mach_header_64 nee_header;
#define nee_getsectbynamefromheader getsectbynamefromheader_64
#else
    typedef uint32_t nee_value;
    typedef struct section nee_section;
    typedef struct mach_header nee_header;
#define nee_getsectbynamefromheader getsectbynamefromheader
#endif
    
    
    uint32_t image_count = _dyld_image_count();
    for (uint32_t image_index = 0; image_index < image_count; image_index++) {
        const nee_header *mach_header = (const nee_header *) _dyld_get_image_header(image_index);
        
        unsigned long size;
        nee_entry *data = (nee_entry *) getsectiondata(mach_header, NEESegmentName, NEESectionName, &size);
        if (data == NULL) {
            continue;
        }
        size_t count = size / sizeof(nee_entry);
        for (size_t i = 0; i < count; i++) {
            nee_entry *entry = &data[i];
            NEELoaderEntryExt *item = [[NEELoaderEntryExt alloc] initWithCategory:*entry->category
                                                                           module:*entry->module
                                                                             name:*entry->name
                                                                         stageKey:*entry->stage_key
                                                                            value:entry->value
                                                                         encoding:*entry->encoding];
            
            if (entry->info) {
                item.info = entry->info;
                NSAssert(item.argsCount == 0 || item.argsCount == 1, @"key: %@, item: %@, 不支持的参数数量 %d, 只支持0个 或 1个参数", item.stage_key, item.name, item.argsCount);
            }
            
            [_store addItem:item];
        }
    }
}

- (NSString *)env:(NSString *)key {
    return self.store.envStore[key].envValue;
}

#ifdef DEBUG

#define NEE_EXECUTE_TRY_CATCH(__task_) __task_

#else

#define NEE_EXECUTE_TRY_CATCH(__task_) \
@try { \
__task_ \
} \
@catch (NSException *exception) { }\
@finally { }

#endif

#define NEE_EXECUTE_LOG_TASK(__task_) \
if (self.enableLog) { \
CFAbsoluteTime startTime = CFAbsoluteTimeGetCurrent(); \
__task_ \
CFAbsoluteTime endTime = CFAbsoluteTimeGetCurrent(); \
item.spendTime = 1000 * (endTime - startTime); \
} \
else { \
 __task_ \
}

- (void)execute:(NSString *)stageKey args:(NSArray *)args {
    __auto_type items = self.store.functionStore[stageKey];
    
    if (items.count == 0) {
#ifdef DEBUG
        NSLog(@"stage_key : %@ 没有要执行的任务", stageKey);
#endif
    }
    
    [items enumerateObjectsWithOptions:NSEnumerationReverse usingBlock:^(NEELoaderEntryExt * _Nonnull item, NSUInteger idx, BOOL * _Nonnull stop) {
        NEE_EXECUTE_TRY_CATCH({
            NEE_EXECUTE_LOG_TASK({
                [self executeWithItem:item args:args];
            })
        });
    }];
}

- (void)executeWithItem:(NEELoaderEntryExt *)item args:(NSArray *)args {
    
    int registerCount = item.argsCount;
    
    if (registerCount == -1) {
        NSAssert(NO, @"key: %@, item: %@ 未声明 参数数量", item.stage_key, item.name);
        return;
    }
    
    switch (registerCount) {
        case 0: {
            __auto_type func = *(void (*(*))(void))item.imp;
            func();
            break;
        }
        case 1: {
            __auto_type func = *(void (*(*))(id))item.imp;
            func(args);
            break;
        }
        default: {
            NSAssert(NO, @"key: %@, item: %@, 不支持的参数数量 %d, 只支持0个 或 1个参数", item.stage_key, item.name, registerCount);
        }
    }
    
}

@end
