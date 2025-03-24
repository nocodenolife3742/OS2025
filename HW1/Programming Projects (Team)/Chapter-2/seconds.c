#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/jiffies.h>
#include <linux/seq_file.h>

#define PROC_FILENAME "seconds"

static struct proc_dir_entry *proc_file;
static unsigned long start_jiffies;

static int seconds_show(struct seq_file *m, void *v) {
    // kernel space does not support floating point, so
    // we use integer arithmetic instead
    const unsigned long elapsed_jiffies = jiffies - start_jiffies;
    const unsigned long seconds = elapsed_jiffies / HZ;
    const unsigned long milliseconds = (elapsed_jiffies % HZ) * 1000 / HZ;
    seq_printf(m, "%lu.%03lu\n", seconds, milliseconds);
    return 0;
}

static int seconds_open(struct inode *inode, struct file *file) {
    return single_open(file, seconds_show, NULL);
}

static const struct proc_ops seconds_ops = {
    .proc_open = seconds_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init seconds_module_init(void) {
    proc_file = proc_create(PROC_FILENAME, 0, NULL, &seconds_ops);
    if (!proc_file)
        return -ENOMEM;
    start_jiffies = jiffies;
    pr_info("/proc/%s created\n", PROC_FILENAME);
    return 0;
}

static void __exit seconds_module_exit(void) {
    remove_proc_entry(PROC_FILENAME, NULL);
    pr_info("/proc/%s removed\n", PROC_FILENAME);
}

module_init(seconds_module_init);
module_exit(seconds_module_exit);

MODULE_AUTHOR("OS Group <ericncnl3742@gmail.com>");
MODULE_DESCRIPTION("A /proc file that displays seconds.");
MODULE_LICENSE("GPL");

