#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "ap_config.h"

static int gci_handler(request_rec *req){
    if(strcmp(req->handler, "gci")){
        return DECLINED;
    }
    if(!req->header_only){
        ap_rputs("<h1>GCI 2019</h1>", req);
    }

    req -> content_type = "text/html;charset=UTF-8";

    apr_table_set(req->headers_out, "X-Content-Type-Options", "nosniff");

    return OK;
}

static void gci_register_hooks(apr_pool_t *p)
{
    printf("gci_register_hooks works!");
    ap_hook_handler(gci_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

module AP_MODULE_DECLARE_DATA gci_module = {
STANDARD20_MODULE_STUFF, 
    NULL, /* create per-dir    config structures */
    NULL, /* merge  per-dir    config structures */
    NULL, /* create per-server config structures */
    NULL, /* merge  per-server config structures */
    NULL, /* table of config file commands       */
    gci_register_hooks  /* register hooks */
};

