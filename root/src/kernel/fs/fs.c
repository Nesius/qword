#include <fs/fs.h>
#include <fd/vfs/vfs.h>
#include <proc/task.h>

void init_fs_devfs(void);
void init_fs_echfs(void);
void init_fs_iso9660(void);

void init_fs(void) {
    init_fs_devfs();
    init_fs_echfs();
    init_fs_iso9660();

    /* Launch the fs cache sync worker */
    task_tcreate(0, tcreate_fn_call, tcreate_fn_call_data(vfs_sync_worker, 0));
}
