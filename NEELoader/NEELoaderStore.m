//
//  NEELoaderStore.m
//  SnailReader
//
//  Created by F_knight on 2019/4/15.
//  Copyright © 2019 com.netease. All rights reserved.
//

#import "NEELoaderStore.h"
#import "NEELoaderAnnotation.h"

@implementation NEELoaderEntryExt {
    NEEEntryType _type;
}

- (instancetype)initWithCategory:(NSString *)category module:(NSString *)module name:(NSString *)name stageKey:(NSString *)stageKey value:(void *)value encoding:(char *)encoding {
    if (self = [super init]) {
        self.category = category;
        self.module = module;
        self.name = name;
        self.stage_key = stageKey;
        self.value = value;
        self.encoding = encoding;
    }
    return self;
}

#pragma mark - Setter & Getter Methods
- (NEEEntryType)type {
    if (_type == 0) {
        if (strcmp(self.encoding, NEEncodingFUNC) == 0) {
            _type = NEEEntryTypeFunc;
        }
        else if (strcmp(self.encoding, NEEncodingENV) == 0) {
            _type = NEEEntryTypeENV;
        }
    }
    return _type;
}

- (NSString *)envValue {
    if (self.type == NEEEntryTypeENV) {
        return *(NEE_Unsafe_String *)self.value;
    }
    return nil;
}

- (void *)imp {
    if (self.type == NEEEntryTypeFunc) {
        return self.value;
    }
    return NULL;
}

- (int)argsCount {
    if (self.info && self.type == NEEEntryTypeFunc) {
        return *(int *)self.info;
    }
    return -1;
}

@end

@implementation NEELoaderStore

- (instancetype)init {
    if (self = [super init]) {
        self.functionStore = [NSMutableDictionary dictionaryWithCapacity:20];
        self.envStore = [NSMutableDictionary dictionaryWithCapacity:20];
    }
    return self;
}

- (void)addItem:(NEELoaderEntryExt *)item {
    if (item.type == NEEEntryTypeFunc) {
        NSMutableArray *imps = self.functionStore[item.stage_key];
        if (!imps) {
            imps = [NSMutableArray array];
            self.functionStore[item.stage_key] = imps;
        }
        [imps addObject:item];
    }
    else if (item.type == NEEEntryTypeENV) {
        self.envStore[item.stage_key] = item;
    }
    else {
        NSAssert(NO, @"item: %@, 不合法entry类型 entry type: %d", item.name, (int)item.type);
    }
}

@end
