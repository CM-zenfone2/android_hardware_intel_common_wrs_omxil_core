/*
 * Copyright (c) 2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef __CMODULE_H
#define __CMODULE_H

#include <module.h>

/*
 * WRS OMX-IL Component Module Symbol
 */
#define WRS_OMXIL_CMODULE_SYMBOL            WRS_OMXIL_CMODULE
#define WRS_OMXIL_CMODULE_SYMBOL_STRING     "WRS_OMXIL_CMODULE"

struct wrs_omxil_cmodule_ops_s {
    OMX_ERRORTYPE (*instantiate)(OMX_PTR *);
};

struct wrs_omxil_cmodule_s {
    const char *name;

    const char **roles;
    const int nr_roles;

    struct wrs_omxil_cmodule_ops_s *ops;
};

class ComponentBase;

class CModule {
 public:
    CModule(const OMX_STRING lname);
    ~CModule();

    /*
     * library loading / unloading
     */
    OMX_ERRORTYPE Load(int flag);
    OMX_U32 Unload(void);

    /* end of library loading / unloading */

    /*
     * accessor
     */
    /* library name */
    const OMX_STRING GetLibraryName(void);

    /* component name and roles */
    const OMX_STRING GetComponentName(void);
    OMX_ERRORTYPE GetComponentRoles(OMX_U32 *nr_roles, OMX_U8 **roles);

    bool QueryHavingThisRole(const OMX_STRING role);

    /* end of accessor */

    /* library symbol method and helpers */
    OMX_ERRORTYPE QueryComponentNameAndRoles(void);
    OMX_ERRORTYPE InstantiateComponent(ComponentBase **instance);

    /* end of library symbol method and helpers */

 private:
    /*
     * library symbol
     */
    struct wrs_omxil_cmodule_s *wrs_omxil_cmodule;

    /* end of library symbol */

    /* component name */
    char cname[OMX_MAX_STRINGNAME_SIZE];

    /* component roles */
    OMX_U8 **roles;
    OMX_U32 nr_roles;

    /* library name */
    char lname[OMX_MAX_STRINGNAME_SIZE];
    /* utils::module */
    struct module *module;
};

#endif /* __CMODULE_H */
