#include <cstdio>
#include <iostream>
#include <format>

#include "memflow.hpp"
OsInstance<> os;

int main(int argc, char* argv[]) 
{
    const char* conn_name = argc > 1 ? argv[1] : "qemu";
    const char* conn_arg = argc > 2 ? argv[2] : "";
    const char* os_name = argc > 3 ? argv[3] : "win32";
    const char* os_arg = argc > 4 ? argv[4] : "";


    log_init(LevelFilter::LevelFilter_Info);
    Inventory* inventory = inventory_scan();

    if (!inventory) {
        log_error("unable to create inventory");
        return 0;
    }

    printf("inventory initialized: %p\n", (void*)inventory);

    ConnectorInstance<> connector, * conn = conn_name[0] ? &connector : nullptr;

    if (conn) {
        if (inventory_create_connector(inventory, conn_name, conn_arg, &connector)) {
            printf("unable to initialize connector\n");
            inventory_free(inventory);
            return 0;
        }
        printf("connector initialized: %p\n", connector.container.instance.instance);
    }
    if (inventory_create_os(inventory, os_name, os_arg, conn, &os)) {
        printf("unable to initialize OS\n");
        inventory_free(inventory);
        return 0;
    }
    inventory_free(inventory);
    ProcessInstance<CBox<void>, CArc<void>> proc;
    os.process_by_name("explorer.exe", &proc);
    if (!proc.vtbl_process)
    {
        return 0;
    }

    imem gap = 0x1000000;
    proc.virt_page_map_range(gap, 0x0, 0x800000000000,
    [](MemoryRange info)
    {
            std::cout << std::format("Addr:{:016X}\n", info._0);
            std::cout << std::format("Size:{:016X}\n", info._1);
            return true;
    }
    );
    return 1;
}
