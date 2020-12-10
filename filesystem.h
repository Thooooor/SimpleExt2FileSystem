#define MAGICNUM 0xABCD
#define INODENUM 32
#define BLOCKNUM 128

/**
 * 超级块
 **/
typedef struct super_block
{
    int magic_num;
    int free_block_count;
    int free_inode_count;
    int dir_inode_count;
    unsigned int block_map[BLOCKNUM];
    unsigned int inode_map[INODENUM];
} sp_block;


struct inode
{
    unsigned int size;
    unsigned int file_type;
    unsigned int link;
    unsigned int block_point[6];
};

struct dir_item
{
    unsigned int inode_id;
    unsigned int valid;
    unsigned int type;
    char name[121];
};

/**
 * @brief initial Ext2 file system
 * 
 * @return returns 0 on success, -1 otherwise. 
 * 
 * @note This function will initial Ext2 file system named "burger" as a vritual file system
 * If the file system is not found, it will try to create the file, and fill it with zeros of 4 MiB.
 * This function must be called before any calls to disk_read_block() and disk_write_block().
 * This function will fail if the disk is already opened.
 */
int init_system();

/**
 * @brief Open the Ext2 file system.
 * 
 * @return returns 0 on success, -1 otherwise. 
 * 
 * @note This function will open a file system named "burger" as a vritual file system
 * If the file is not found, it will try to create the file, and fill it with zeros of 4 MiB.
 * This function must be called before any calls to disk_read_block() and disk_write_block().
 * This function will fail if the disk is already opened.
 */
int open_system();

/**
 * @brief Close the Ext2 file system. 
 * 
 * @return returns 0 on success, -1 otherwise. 
 * 
 * @note This function will open a file named "disk" as a vritual disk
 * If the file is not found, it will try to create the file, and fill it with zeros of 4 MiB.
 * This function must be called before any calls to disk_read_block() and disk_write_block().
 * This function will fail if the disk is already opened.
 */
int close_system();

int make_dir();

int make_file();

int copy_file();
