/*
 *  CQGlobal.cpp
 *  CQ2Client
 *
 *  Created by 张 立志 on 10-11-28.
 *  Copyright 2010 网龙公司. All rights reserved.
 *
 */

//void _i64toa(I64 i64, char* buf, int radix)
//{
//	if (buf == NULL) {
//		return;
//	}
//
//	*buf = '\0';
//
//	if (radix <= 1 || radix > 36) {
//		return;
//	}
//
//	if (i64 == 0) {
//		buf[0] = '0';
//		buf[1] = '\0';
//		return;
//	}
//
//	char* p = buf;
//	int i = 0;
//	if (i64 < 0) {
//		i64 = -i64;
//		if (i64 < 0) {
//			return; // i64 == LLONG_MIN.
//					// TODO: fix this.
//		}
//		
//		*p++ = '-';
//		++i;
//	}
//
//	const char* chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//
//	while (i64 != 0) {
//		I64 a = i64 % radix;
//		i64 /= radix;
//		*p++ = chars[a];
//		++i;
//	}
//
//	*p = '\0';
//	
//	char c = 0;
//	int beg = 0;
//	int end = i - 1;
//	while (beg < end) {
//		c = buf[beg];
//		buf[beg] = buf[end];
//		buf[end] = c;
//		++beg;
//		--end;
//	}
//}
