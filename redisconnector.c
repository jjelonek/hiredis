//
//  redisconnector.c
//  redisconnector
//
//  Created by Jacek Jelonek on 28/10/14.
//  Copyright (c) 2014 recoded. All rights reserved.
//


//#include "fmacros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <strings.h>
//#include <sys/time.h>
#include <stddef.h>
#include <assert.h>
//#include <unistd.h>
//#include <signal.h>
//#include <errno.h>
//#include <limits.h>

#include "hiredis.h"
#include "redisconnector.h"


static redisContext* c;

int openRedis(char *host, int port){
	c = redisConnect(host, port);
	if (c == NULL) {
        printf("Connection error: can't allocate redis context\n");
        exit(1);
    } 
	return c->err;
}

int closeRedis(){
    redisReply *reply;
	reply = redisCommand(c,"FLUSHDB");
    assert(reply != NULL);
    freeReplyObject(reply);
	return reply->type;
}

int execRedisCmd(char *cmd, char *replyStr, int *replyInt){	
    redisReply *reply;
	reply = redisCommand(c, cmd);
    assert(reply != NULL);
	int res = reply->type;
	switch(res){
		case REDIS_REPLY_STRING:
		case REDIS_REPLY_ERROR:
			strncpy(reply->str, replyStr, reply->len);
			break;
		case REDIS_REPLY_INTEGER:
			*replyInt = reply->integer;
			break;
		case REDIS_REPLY_NIL:
		case REDIS_REPLY_STATUS:
		case REDIS_REPLY_ARRAY:
			break;
	}
    freeReplyObject(reply);
    return res;
}

