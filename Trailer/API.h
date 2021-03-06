
#define TRAILER_GITHUB_REPO @"http://dev.housetrip.com/trailer/"
#define LOW_API_WARNING 0.20

typedef enum {
	kNewComment = 0,
	kNewPr,
	kPrMerged,
	kPrReopened,
	kNewMention,
	kPrClosed,
	kNewRepoSubscribed,
	kNewRepoAnnouncement,
	kNewPrAssigned
} PRNotificationType;

typedef enum {
	kCreationDate = 0,
	kRecentActivity,
	kTitle,
	kRepository,
} PRSortingMethod;

typedef enum {
	kRepoAutoSubscribeNone = 0,
	kRepoAutoSubscribeParentsOnly,
	kRepoDontAutoSubscribeAll,
} PRSubscriptionPolicy;

typedef enum {
	kPullRequestHandlingKeepMine = 0,
	kPullRequestHandlingKeepAll,
	kPullRequestHandlingKeepNone,
} PRHandlingPolicy;

#define PULL_REQUEST_ID_KEY @"pullRequestIdKey"
#define COMMENT_ID_KEY @"commentIdKey"
#define NOTIFICATION_URL_KEY @"urlKey"

#define RATE_UPDATE_NOTIFICATION @"RateUpdateNotification"

#define NETWORK_TIMEOUT 120.0
#define BACKOFF_STEP 120.0

@interface API : NSObject

@property (nonatomic) NSString *resetDate;
@property (nonatomic) float requestsLimit, requestsRemaining;
@property (nonatomic) Reachability *reachability;
@property (nonatomic) long successfulRefreshesSinceLastStatusCheck;

- (void)updateLimitFromServer;

- (void)fetchRepositoriesAndCallback:(void(^)(BOOL success))callback;

- (void)fetchPullRequestsForActiveReposAndCallback:(void(^)(BOOL success))callback;

- (void)getRateLimitAndCallback:(void(^)(long long remaining, long long limit, long long reset))callback;

- (void)testApiAndCallback:(void(^)(NSError *error))callback;

- (void)expireOldImageCacheEntries;

- (void)clearImageCache;

- (void)restartNotifier;

- (NSString *)lastUpdateDescription;

- (BOOL)haveCachedAvatar:(NSString *)path
	  tryLoadAndCallback:(void(^)(IMAGE_CLASS *image))callbackOrNil;

@end
