
/**
 * 超级块
 **/
typedef struct super_block
{
    int magic_num;
    int free_block_count;
    int free_inode_count;
    int dir_inode_count;
    unsigned int block_map[128];
    unsigned int inode_map[32];
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


