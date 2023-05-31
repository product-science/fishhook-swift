//
//  myhooks.c
//  interpose
//
//  Created by Vitaly Khudobakhshov on 04/04/2023.
//
#include "fishhook.h"
#include "myhooks.h"

extern void *transformBlock(void *, void *);

/*
 (extension in Dispatch):__C.OS_dispatch_queue.async(group: Swift.Optional<__C.OS_dispatch_group>, qos: Dispatch.DispatchQoS, flags: Dispatch.DispatchWorkItemFlags, execute: @convention(block) () -> ()) -> ()
 */
static void (*__org_async)(void *, void *, void *, void *);

void __new_async(void *group, void *qos, void *flags, void *block)
{
    uint64_t self;
    asm volatile("mov %0, x20" : "=r"(self) ::);
    void *b = transformBlock(block, (void *)self);
    __org_async(group, qos, flags, b);
}

void install_my_hooks(void)
{
    rebind_symbols((struct rebinding[1]){
        {"$sSo17OS_dispatch_queueC8DispatchE5async5group3qos5flags7executeySo0a1_b1_F0CSg_AC0D3QoSVAC0D13WorkItemFlagsVyyXBtF", __new_async, (void *)&__org_async}
    }, 1);
    printf("Original function pointer is %p\n", __org_async);
}

