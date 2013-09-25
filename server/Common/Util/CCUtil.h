/**
 * PAP Server Engine ( https://github.com/viticm/web-pap )
 * $Id CCUtil.h
 * @link https://github.com/viticm/web-pap/tree/master/server for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-8-23 20:01:52
 * @uses the useful functions, more will be static function
 */
#include <stdio.h>
#include <string.h>
#include <iconv.h>

typedef std::string STRING

class CCUtil
{

public:
    CCUtil() ;
    ~CCUtil() ;

public:
    static int charsetConvert( const char* from, const char* to, char* save, int savelen, char* src, int srclen ) ;
    static STRING StrReplace( STRING str, STRING search_str, STRING replace_str ) ;
} ;
