#include <iostream>
#include "memflow.hpp"

OsInstance<> os;

int main(int argc, char *argv[]) {
        log_init(LevelFilter::LevelFilter_Info);
        Inventory *inventory = inventory_scan();

        if (!inventory) {
                log_error("unable to create inventory");
                return 1;
        }

        printf("inventory initialized: %p\n", (void*)inventory);

        const char *conn_name = argc > 1? argv[1]: "qemu";
        const char *conn_arg = argc > 2? argv[2]: "";
        const char *os_name = argc > 3? argv[3]: "win32";
        const char *os_arg = argc > 4? argv[4]: "";

        ConnectorInstance<> connector, *conn = conn_name[0] ? &connector : nullptr;

        if (conn) {
                if (inventory_create_connector(inventory, conn_name, conn_arg, &connector)) {
                        printf("unable to initialize connector\n");
                        inventory_free(inventory);
                        return 1;
                }

                printf("connector initialized: %p\n", connector.container.instance.instance);
        }

        if (inventory_create_os(inventory, os_name, os_arg, conn, &os)) {
                printf("unable to initialize OS\n");
                inventory_free(inventory);
                return 1;
        }

        inventory_free(inventory);

}
