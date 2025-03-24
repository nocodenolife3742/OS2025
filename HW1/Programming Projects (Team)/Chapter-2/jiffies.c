#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/jiffies.h>
#include <linux/seq_file.h>

#define PROC_FILENAME "jiffies"

static struct proc_dir_entry *proc_file;

static int jiffies_show(struct seq_file *m, void *v) {
    seq_printf(m, "%lu\n", jiffies);
    return 0;
}

static int jiffies_open(struct inode *inode, struct file *file) {
    return single_open(file, jiffies_show, NULL);
}

static const struct proc_ops jiffies_ops = {
    .proc_open = jiffies_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init jiffies_module_init(void) {
    proc_file = proc_create(PROC_FILENAME, 0, NULL, &jiffies_ops);
    if (!proc_file)
        return -ENOMEM;
    pr_info("/proc/%s created\n", PROC_FILENAME);
    return 0;
}

static void __exit jiffies_module_exit(void) {
    remove_proc_entry(PROC_FILENAME, NULL);
    pr_info("/proc/%s removed\n", PROC_FILENAME);
}

module_init(jiffies_module_init);
module_exit(jiffies_module_exit);

MODULE_AUTHOR("OS Group <ericncnl3742@gmail.com>");
MODULE_DESCRIPTION("A /proc file that displays jiffies.");
MODULE_LICENSE("GPL");

