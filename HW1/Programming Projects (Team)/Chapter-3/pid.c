#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/sched/signal.h>

#define PROC_FILENAME "pid"

static struct proc_dir_entry *proc_file;
static int stored_pid = -1;

static int pid_show(struct seq_file *m, void *v) {
    struct task_struct *task;
    
    if (stored_pid == -1) {
        seq_puts(m, "No PID stored\n");
        return 0;
    }
    
    task = pid_task(find_get_pid(stored_pid), PIDTYPE_PID);
    if (!task) {
        seq_printf(m, "PID %d not found\n", stored_pid);
        return 0;
    }
    
    seq_printf(m, "command = [%s] pid = [%d] state = [%u]\n",
               task->comm, task->pid, task->__state);
    
    return 0;
}

static int pid_open(struct inode *inode, struct file *file) {
    return single_open(file, pid_show, NULL);
}

static ssize_t pid_write(struct file *file, const char __user *ubuf, size_t count, loff_t *ppos) {
    char buf[256];
    if (count > sizeof(buf) - 1)
        return -EINVAL;
    
    if (copy_from_user(buf, ubuf, count))
        return -EFAULT;
    
    buf[count] = '\0';
    if (kstrtoint(buf, 10, &stored_pid))
        return -EINVAL;
    
    return count;
}

static const struct proc_ops pid_ops = {
    .proc_open = pid_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
    .proc_write = pid_write,
};

static int __init pid_module_init(void) {
    proc_file = proc_create(PROC_FILENAME, 0666, NULL, &pid_ops);
    if (!proc_file)
        return -ENOMEM;
    pr_info("/proc/%s created\n", PROC_FILENAME);
    return 0;
}

static void __exit pid_module_exit(void) {
    remove_proc_entry(PROC_FILENAME, NULL);
    pr_info("/proc/%s removed\n", PROC_FILENAME);
}

module_init(pid_module_init);
module_exit(pid_module_exit);

MODULE_AUTHOR("OS Group <ericncnl3742@gmail.com>");
MODULE_DESCRIPTION("A /proc file to display process information.");
MODULE_LICENSE("GPL");
