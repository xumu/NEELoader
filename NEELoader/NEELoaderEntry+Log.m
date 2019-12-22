//
//  NEELoaderEntry+Log.m
//  SnailReader
//
//  Created by F_knight on 2019/4/16.
//  Copyright © 2019 com.netease. All rights reserved.
//

#import "NEELoaderEntry+Log.h"
#import <objc/runtime.h>

@implementation NEELoaderEntry (Log)

- (NSTimeInterval)spendTime {
    NSNumber *spendTime = objc_getAssociatedObject(self, @selector(spendTime));
    
    if (spendTime) {
        return [spendTime doubleValue];
    }
    return 0;
}

- (void)setSpendTime:(NSTimeInterval)spendTime {
    objc_setAssociatedObject(self, @selector(spendTime), @(spendTime), OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

@end
