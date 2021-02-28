/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- *//* ***** BEGIN LICENSE BLOCK ***** * Version: NPL 1.1/GPL 2.0/LGPL 2.1 * * The contents of this file are subject to the Netscape Public License * Version 1.1 (the "License"); you may not use this file except in * compliance with the License. You may obtain a copy of the License at * http://www.mozilla.org/NPL/ * * Software distributed under the License is distributed on an "AS IS" basis, * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License * for the specific language governing rights and limitations under the * License. * * The Original Code is mozilla.org code. * * The Initial Developer of the Original Code is  * Netscape Communications Corporation. * Portions created by the Initial Developer are Copyright (C) 1998 * the Initial Developer. All Rights Reserved. * * Contributor(s): * * Alternatively, the contents of this file may be used under the terms of * either the GNU General Public License Version 2 or later (the "GPL"), or  * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"), * in which case the provisions of the GPL or the LGPL are applicable instead * of those above. If you wish to allow use of your version of this file only * under the terms of either the GPL or the LGPL, and not to allow others to * use your version of this file under the terms of the NPL, indicate your * decision by deleting the provisions above and replace them with the notice * and other provisions required by the GPL or the LGPL. If you do not delete * the provisions above, a recipient may use your version of this file under * the terms of any one of the NPL, the GPL or the LGPL. * * ***** END LICENSE BLOCK ***** */#ifndef nsGenericFactory_h___#define nsGenericFactory_h___#include "nsCOMPtr.h"#include "nsIGenericFactory.h"#include "nsIClassInfo.h"/** * Most factories follow this simple pattern, so why not just use a function * pointer for most creation operations? */class nsGenericFactory : public nsIGenericFactory, public nsIClassInfo {public:    NS_DEFINE_STATIC_CID_ACCESSOR(NS_GENERICFACTORY_CID);    nsGenericFactory(const nsModuleComponentInfo *info = NULL);    virtual ~nsGenericFactory();        NS_DECL_ISUPPORTS    NS_DECL_NSICLASSINFO        /* nsIGenericFactory methods */    NS_IMETHOD SetComponentInfo(const nsModuleComponentInfo *info);    NS_IMETHOD GetComponentInfo(const nsModuleComponentInfo **infop);    NS_IMETHOD CreateInstance(nsISupports *aOuter, REFNSIID aIID, void **aResult);    NS_IMETHOD LockFactory(PRBool aLock);    static NS_METHOD Create(nsISupports* outer, const nsIID& aIID, void* *aInstancePtr);private:    const nsModuleComponentInfo *mInfo;};////////////////////////////////////////////////////////////////////////////////#include "nsIModule.h"#include "plhash.h"class nsGenericModule : public nsIModule{public:    nsGenericModule(const char* moduleName,                     PRUint32 componentCount,                    const nsModuleComponentInfo* components,                    nsModuleConstructorProc ctor,                    nsModuleDestructorProc dtor);    virtual ~nsGenericModule();    NS_DECL_ISUPPORTS    NS_DECL_NSIMODULE    struct FactoryNode    {        FactoryNode(nsIGenericFactory* fact, FactoryNode* next)         {             mFactory = fact;             mNext    = next;        }        ~FactoryNode(){}        nsCOMPtr<nsIGenericFactory> mFactory;        FactoryNode* mNext;    };protected:    nsresult Initialize(nsIComponentManager* compMgr);    void Shutdown();    nsresult AddFactoryNode(nsIGenericFactory* fact);    PRBool                       mInitialized;    const char*                  mModuleName;    PRUint32                     mComponentCount;    const nsModuleComponentInfo* mComponents;    FactoryNode*                 mFactoriesNotToBeRegistered;    nsModuleConstructorProc      mCtor;    nsModuleDestructorProc       mDtor;};#endif /* nsGenericFactory_h___ */