#ifndef _STRINGS_H_
#define _STRINGS_H_

typedef void* String;

#define createString(s) (String)_str_create(s)
#define destroyString(s) _str_destroy(s)
#define appendStringChar(s, c) _str_append_char((s), (c))
#define appendStringStr(s, p) _str_append_str((s), (p))
#define appendStringString(s, p) _str_append_string((s), (p))
#define appendStringFormat(s, p, ...) _str_append_format((s), (p), ##__VA_ARGS__)
#define insertStringFormat(s, i, p, ...) _str_insert_format((s), (i), (p), ##__VA_ARGS__)
#define findStringChar(s, i, c) _str_find_char((s), (i), (c))
#define findStringRevChar(s, i, c) _str_find_rev_char((s), (i), (c))
#define replaceStringChar(s, i, c) _str_repl_char((s), (i), (c))
#define truncateString(s, i) _str_truncate((s), (i))
#define rawString(s) _str_raw(s)
#define resetString(s) _str_reset(s)
#define iterateString(s) _str_iterate(s)

struct _string_* _str_create(const char* str);
void _str_destroy(struct _string_* str);
int _str_append_char(struct _string_* str, int ch);
int _str_append_str(struct _string_* str, const char* ptr);
int _str_append_string(struct _string_* str, struct _string_* ptr);
int _str_append_format(struct _string_* str, const char* ptr, ...);
const char* _str_raw(struct _string_* str);
void _str_reset(struct _string_* str);
int _str_iterate(struct _string_* str);
int _str_find_char(struct _string_* str, int index, int ch);
void _str_repl_char(struct _string_* str, int index, int ch);
int _str_find_rev_char(struct _string_* str, int index, int ch);
int _str_insert_format(struct _string_* str, int index, const char* val, ...);
void _str_truncate(struct _string_* str, int index);

#endif
