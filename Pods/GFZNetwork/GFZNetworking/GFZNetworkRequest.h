//
//  GFZNetworkRequest.h
//  GFZNetwork
//
//  Created by 610582 on 2019/8/27.
//  Copyright © 2019 GFZ. All rights reserved.
//

#import "GFZBaseRequest.h"
@class GFZNetworkRequest, GFZNetworkBatchRequest;

NS_ASSUME_NONNULL_BEGIN

@interface GFZResponseModel : NSObject
@property (nonatomic, assign, readonly) BOOL                        isSuccess;
@property (nonatomic, assign, readonly) BOOL                        isCacheData;
@property (nonatomic, assign, readonly) CGFloat                     responseDuration;
@property (nonatomic, assign, readonly) NSInteger                   responseCode;
@property (nonatomic, strong, readonly, nullable) id                responseModel;
@property (nonatomic, strong, readonly, nullable) id responseObject;//NSDictionary/UIImage/NSData/...
@property (nonatomic, strong, readonly, nullable) NSDictionary      *responseDict;
@property (nonatomic, copy  , readonly, nullable) NSString          *responseMsg;
@property (nonatomic, strong, readonly, nullable) NSError           *error;
@property (nonatomic, strong, readonly, nullable) NSHTTPURLResponse *urlResponse;
@property (nonatomic, strong, readonly, nullable) NSURLRequest      *originalRequest;
@end


@protocol GFZNetworkDelegate <NSObject>
/**
 网络请求数据响应回调

 @param request 请求对象
 @param responseModel 响应对象
 */
- (void)gfzResponseWithRequest:(GFZNetworkRequest *)request
                 responseModel:(GFZResponseModel *)responseModel;
@end


@protocol GFZNetworkBatchDelegate <GFZNetworkDelegate>
/**
 多个网络请求完成后响应一次回调

 @param batchRequest 请求对象数组
 @param responseModelArray 响应对象数组
 */
- (void)gfzBatchResponseWithRequest:(GFZNetworkBatchRequest *)batchRequest
                         modelArray:(NSArray<GFZResponseModel *> *)responseModelArray;
@end


@protocol GFZNetworkMulticenter <NSObject>
/**
 * 网络请求将要开始回调
 * @param request 请求对象
 */
- (void)requestWillStart:(GFZNetworkRequest *)request;

/**
 * 网络请求回调将要停止 (包括成功或失败)
 * @param responseModel 请求对象
 */
- (void)requestWillStop:(GFZNetworkRequest *)request responseModel:(GFZResponseModel *)responseModel;

/**
 * 网络请求已经回调完成 (包括成功或失败)
 * @param responseModel 请求对象
 */
- (void)requestDidCompletion:(GFZNetworkRequest *)request responseModel:(GFZResponseModel *)responseModel;

@end



@interface GFZNetworkRequest : GFZBaseRequest


/** 请求是否需要缓存 */
@property (nonatomic, assign) BOOL      autoCacheResponse;

/** 请求成功返回后解析成相应的Model返回 */
@property (nonatomic, strong) Class     responseModelCalss;

/** 请求转圈的父视图 */
@property (nonatomic, strong) UIView    *loadingSuperView;

/** 请求失败之后重新请求次数*/
@property (nonatomic, assign) NSInteger retryCountWhenFailure;

/**
 * 网络请求过程多通道回调<将要开始, 将要停止, 已经完成>
 * 注意: 如果没有实现此代理则会回调单例中的全局代理<globleMulticenterDelegate>
 */
@property (nonatomic, weak) id<GFZNetworkMulticenter> multicenterDelegate;

/** 可以用来添加几个accossories对象 来做额外的(请求HUD, 加解密, 自定义打印, 上传统计)插件等特殊功能 */
@property (nonatomic, strong) NSArray<id<GFZNetworkMulticenter>> *requestAccessories;

/*
 * 缓存key, 可用于清除指定请求
 */
- (NSString *)cacheKey;

/*
 * 单个网络请求->代理回调
 * @parm networkDelegate 请求成功失败回调代理
 */
- (NSURLSessionDataTask *)startRequestWithDelegate:(id<GFZNetworkDelegate>)responseDelegate;

/*
 * 单个网络请求->Block回调
 * @parm responseBlock 请求响应block
 */
- (NSURLSessionDataTask *)startRequestWithBlock:(GFZNetworkResponseBlock)responseBlock;

/**
 * 取消局部请求链接。（可用于用户退出界面，或搜索框连续请求这样的需求）
 */
+ (void)cancelRequestsWithApiList:(NSArray<GFZNetworkRequest *> *)requestList;

/**
 * 取消全局请求管理数组中所有请求操作 (可在注销,退出登录,内存警告时调用此方法)
 */
+ (void)cancelGlobleAllRequestMangerTask;

@end


@interface GFZNetworkBatchRequest : NSObject

/** 批量请求是否都请求成功了 */
@property(nonatomic, assign, readonly) BOOL isAllSuccess;

/**
 * 便捷初始化多并发请求函数
 * @param requestArray 请求GFZNetworkRequest对象数组
 * @return 多并发请求对象
 */
+ (instancetype)batchArrayRequest:(NSArray<GFZNetworkRequest *> *)requestArray;

/**
 批量网络请求

 @param responseDelegate 请求全部完成后的响应代理回调
 @param shouldAllSuccess 是否等待全部请求完成才回调
 */
- (void)startRequestWithDelegate:(id<GFZNetworkBatchDelegate>)responseDelegate
                  waitAllSuccess:(BOOL)shouldAllSuccess;

/**
 批量网络请求

 @param responseBlock 请求全部完成后的响应block回调
 @param shouldAllSuccess 是否等待全部请求完成才回调
 */
- (void)startRequestWithBlock:(GFZNetworkBatchBlock)responseBlock
               waitAllSuccess:(BOOL)shouldAllSuccess;

@end

NS_ASSUME_NONNULL_END
