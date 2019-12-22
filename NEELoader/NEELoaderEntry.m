//
//  NEELoaderEntry.m
//  SnailReader
//
//  Created by F_knight on 2019/4/15.
//  Copyright © 2019 com.netease. All rights reserved.
//

#import "NEELoaderEntry.h"
#import "NEELoaderAnnotation.h"

@implementation NEELoaderEntry {
    NSString *_identity;
}

- (instancetype)initWithCategory:(NSString *)category module:(NSString *)module name:(NSString *)name stage_key:(NSString *)stage_key {
    if (self = [super init]) {
        self.category = category;
        self.module = module;
        self.name = name;
        self.stage_key = stage_key;
    }
    return self;
}

- (instancetype)initWithName:(NSString *)name stage_key:(NSString *)stage_key {
    return [self initWithCategory:NEE_CATEGORY_PREFIX_DEFAULT module:NEE_MODULE_PREFIX_DEFAULT name:name stage_key:stage_key];
}

- (NSString *)identify {
    if (!_identity) {
        _identity = [NSString stringWithFormat:@"%@_%@_%@", self.category, self.module, self.name];
    }
    return _identity;
}

@end
