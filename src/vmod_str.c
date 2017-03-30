#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "vrt.h"
#include "vcc_if.h"
#include "cache.h"


typedef struct sess re_ctx;


int
vmod_atoi(struct sess *sp, const char *int_string)
{
    // this is a trivial converter for unix timestamps for now, we
    // need to turn it into a factory for all the different potential
    // formats it could discover (RFC 1123, etc.)
    int value;
    if (sscanf(int_string, "%i", &value) != 1) {
        return 0;
    }
    return value;
}


const char *
vmod_ifs(struct sess *sp, unsigned condition, const char *string1, const char *string2)
{
    if (condition) {
        return string1;
    }
    return string2;
}


const char *
vmod_strstr(struct sess *sp, const char *haystack, const char *needle)
{
    char *result;
    char *match;
    unsigned length = 0;
    unsigned available = WS_Reserve(sp->wrk->ws, 0);

    if (available == 0) {
        WS_Release(sp->wrk->ws, 0);
        return NULL;
    }

    result = sp->wrk->ws->f;
    match = strstr(haystack, needle);

    if (match == NULL) {
        result = "";
    } else {
        length = strlen(match);
        if (length > available - 1) {
            length = available - 1;
        }
        memcpy(result, match, length);
        result[length] = '\0';
    }
    length += 1;
    WS_Release(sp->wrk->ws, length);
    return result;
}


const char *
vmod_toupper(struct sess *sp, const char *string)
{
    char *result;
    unsigned index;
    unsigned available = WS_Reserve(sp->wrk->ws, 0);
    unsigned length = strlen(string);

    if (available <= length) {
        WS_Release(sp->wrk->ws, 0);
        return NULL;
    }

    result = sp->wrk->ws->f;

    for (index = 0; index < length; index++) {
        result[index] = toupper(string[index]);
    }
    result[length] = '\0';
    length += 1;

    WS_Release(sp->wrk->ws, length);
    return result;
}


const char *
vmod_tolower(struct sess *sp, const char *string)
{
    char *result;
    unsigned index;
    unsigned available = WS_Reserve(sp->wrk->ws, 0);
    unsigned length = strlen(string);

    if (available <= length) {
        WS_Release(sp->wrk->ws, 0);
        return NULL;
    }

    result = sp->wrk->ws->f;

    for (index = 0; index < length; index++) {
        result[index] = tolower(string[index]);
    }
    result[length] = '\0';
    length += 1;

    WS_Release(sp->wrk->ws, length);
    return result;
}
