//
//  redisconnector.c
//  redisconnector
//
//  Created by Jacek Jelonek on 28/10/14.
//  Copyright (c) 2014 recoded. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include "hiredis.h"
#include "redisconnector.h"


static redisContext* c;

int openRedisDB(char *host, int port){
	c = redisConnect(host, port);
	if (c == NULL) {
        printf("Connection error: can't allocate redis context\n");
        exit(1);
    } 
	return c->err;
}

int execRedisCmd(char *cmd, char *replyStr, char *replyInt){
    redisReply *reply;
	reply = redisCommand(c, cmd);
    assert(reply != NULL);
	int res = reply->type;
	switch(res){
		case REDIS_REPLY_STRING:
		case REDIS_REPLY_ERROR:
		case REDIS_REPLY_STATUS:
			strncpy(replyStr, reply->str, reply->len);
			break;
		case REDIS_REPLY_INTEGER:
			sprintf(replyInt, "%lld", reply->integer);
			break;
		case REDIS_REPLY_NIL:
		case REDIS_REPLY_ARRAY:
			break;
	}
    freeReplyObject(reply);
    return res;
}

