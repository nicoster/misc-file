#include <tchar.h>
#include <crtdbg.h>
enum http_method_t{hm_options, hm_get, hm_head, hm_post, hm_put, hm_delete, hm_trace, hm_max};

static wchar_t *http_method_name[] = 
{
	L"OPTIONS", L"GET", L"HEAD", L"POST", L"PUT", L"DELETE", L"TRACE",
};

wchar_t* get_http_method_name(http_method_t method)
{

	_ASSERTE(method < hm_max);
	return http_method_name[method];
}

http_method_t get_http_method_by_name(wchar_t* method_name)
{
	for (int i = 0; i < hm_max; ++ i)
		if (wcsicmp(method_name, http_method_name[i]) == 0) return (http_method_t)i;

	_ASSERTE(! "invalid http method name");
	return hm_get;
}
