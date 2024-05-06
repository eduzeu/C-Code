
typedef struct {
    int pid;
    char user[64];
    char command[256];
} ProcessInfo;

// Function to compare process information for sorting
int compare_process_info(const void *a, const void *b) {
    const ProcessInfo *p1 = (const ProcessInfo *)a;
    const ProcessInfo *p2 = (const ProcessInfo *)b;
    return p1->pid - p2->pid;
}

// Function to list processes
void do_lp() {
    // Open /proc directory
    DIR *proc_dir = opendir("/proc");
    if (proc_dir == NULL) {
        perror("opendir() error");
        exit(EXIT_FAILURE);
    }

    // Process information array
    ProcessInfo processes[1024];
    int num_processes = 0;

    // Read /proc directory
    struct dirent *entry;
    while ((entry = readdir(proc_dir)) != NULL) {
        // Check if the directory name is a number (PID)
        if (entry->d_type == DT_DIR && atoi(entry->d_name) != 0) {
            // Open /proc/<PID>/cmdline file
            char cmdline_path[512]; // Increased buffer size
            snprintf(cmdline_path, sizeof(cmdline_path), "/proc/%s/cmdline", entry->d_name);
            int cmdline_fd = open(cmdline_path, O_RDONLY);
            if (cmdline_fd != -1) {
                // Read command from /proc/<PID>/cmdline
                ssize_t bytes_read = read(cmdline_fd, processes[num_processes].command, sizeof(processes[num_processes].command) - 1);
                if (bytes_read != -1) {
                    // Null-terminate the command string
                    processes[num_processes].command[bytes_read] = '\0';
                    // Get process ID
                    processes[num_processes].pid = atoi(entry->d_name);
                    // Get user for the process
                    struct stat stat_buf;
                    if (stat(cmdline_path, &stat_buf) != -1) {
                        struct passwd *passwd_entry = getpwuid(stat_buf.st_uid);
                        if (passwd_entry != NULL) {
                            strncpy(processes[num_processes].user, passwd_entry->pw_name, sizeof(processes[num_processes].user));
                        } else {
                            snprintf(processes[num_processes].user, sizeof(processes[num_processes].user), "%d", stat_buf.st_uid);
                        }
                    } else {
                        perror("stat() error");
                        exit(EXIT_FAILURE);
                    }
                    num_processes++;
                } else {
                    perror("read() error");
                    exit(EXIT_FAILURE);
                }
                close(cmdline_fd);
            } else {
                if (errno != ENOENT) {
                    perror("open() error");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }