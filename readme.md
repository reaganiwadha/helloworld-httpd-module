# Hello World Apache HTTPD Module ![GCI Badge](https://img.shields.io/badge/Google%20Code%20In-JBoss%20Community-red?style=flatr&labelColor=fdb900&link=https://codein.withgoogle.com/organizations/jboss-community/)
![Screenshot of its working](https://github.com/reaganiwadha/helloworld-httpd-module/blob/master/screenshot.png?raw=true)
This guide will help you make a hello world module for httpd!

## Prerequisites

* apache2
* apache2-dev
* gcc
* libapache2-mod-wsgi
* python-dev

## Creating the module file

We need to use the c language for the module file, lets name this module file mod_gci.c

### Handler

Declaring the handler

```cpp
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
```

### Hooks

We need to define the hooks so it can call the handler if an event occurs

```cpp
static void gci_register_hooks(apr_pool_t *p)
{
    printf("gci_register_hooks works!");
    ap_hook_handler(helloworld_handler, NULL, NULL, APR_HOOK_MIDDLE);
}
```

### Module Identity

```cpp
module AP_MODULE_DECLARE_DATA gci_module = {
    STANDARD20_MODULE_STUFF,
    NULL, /* create per-dir    config structures */
    NULL, /* merge  per-dir    config structures */
    NULL, /* create per-server config structures */
    NULL, /* merge  per-server config structures */
    NULL, /* table of config file commands       */
    helloworld_register_hooks  /* register hooks */
};
```

Finish result should look like this

```cpp
#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "ap_config.h"

static int gci_handler(request_rec *req){
    if(strcmp(req->, "gci")){
        return DECLINED;
    }
    if(!req->header_only){
        ap_rputs("<h1>GCI 2019</h1>");
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

```

## Compiling and Install the module

To compile the module, use apxs

```bash
apxs -i -a -c mod_gci.c
```

## Enabling module

Go to your httpd.conf file and then add the following

```conf
# httpd.conf
LoadModule gci_module modules/mod_gci.c
<Location /gci>
    SetHandler gci
</Location>
```

## Restarting httpd

```bash
/usr/bin/apachectl restart
```

or

```bash
systemctl restart httpd
```

## Testing
Going to localhost/gci should return you
```html
<h1>GCI 2019</h1>
```

And thats it!
