#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 歌曲节点结构体
typedef struct Song {
    int id;
    char title[100];
    char artist[50];
    char filepath[300];
    struct Song* prev;
    struct Song* next;
} Song;

// 播放列表管理器结构
typedef struct PlaylistManager{
    Song* head;
    Song* tail;
    Song* current;
    int song_count;
} PlaylistManager;

// 函数声明
void init_playlist_manager(PlaylistManager* manager);                           // 初始化管理器
int load_songs_from_file(PlaylistManager* manager, const char* filename);       // 从文件中读取歌曲
void add_song(PlaylistManager* manager, const char* title, const char* artist,  // 手动添加歌曲
              const char* filepath);
int delete_song_by_title(PlaylistManager* manager, const char* title);                   // 删除指定标题的歌曲
int play_song_by_title(PlaylistManager* manager, const char* title);                     // 按标题播放歌曲
void display_playlist(PlaylistManager* manager);                                // 显示播放列表（顺序）
void display_playlist_reverse(PlaylistManager* manager);                        // 显示播放列表（逆序）
int export_playlist(PlaylistManager* manager, const char* filename);            // 导出歌单
void next_song(PlaylistManager* manager);                                       // 下一首歌
void previous_song(PlaylistManager* manager);                                   // 上一首歌
int play_song_random(PlaylistManager* manager);                                 // 随机播放歌曲（非必须）
int insert_song_at(PlaylistManager* manager, int position, const char* title, const char* artist, const char* filepath);    // 在指定位置插入歌曲（非必须）
void clear_playlist(PlaylistManager* manager);                                  // 清空播放列表（非必须）
void sort_by_title(PlaylistManager* manager);                                   // 按歌曲名排序（非必须）


// linux/Mac 版本
// void play_audio(const char* filename) {
//     char command[256];
//     FILE *mp3File = fopen(filename, "rb");
//     if (!mp3File) {
//         printf("无法打开文件 %s\n", filename);
//         return;
//     }
//     else{
//         printf("Founded File!!");
//     }
//     snprintf(command, sizeof(command), "afplay \"%s\"", filename);
//     int ret = system(command);
//     if (ret != 0) {
//         printf("播放失败或中断，检查文件格式是否支持。\n");
//     }
// }

// Windows 版本
// void play_audio(const char* filename){
//     char command[256];
//     FILE *mp3File = fopen(filename, "rb");
//     if (!mp3File) {
//         printf("无法打开文件 %s\n", filename);
//         return;
//     }
//     else{
//         printf("Founded File!!");
//     }
//     snprintf(command, sizeof(command), "start \"\" \"%s\"", filename);
//     int ret = system(command);
//     if (ret != 0) {
//         printf("播放失败或中断，检查文件格式是否支持。\n");
//     }
    
//     // 或者使用 Windows Media Player
//     // sprintf(command, "wmplayer \"%s\"", filename);
//     // system(command);
// }

void play_audio(const char* filename){
    printf("Playing %s ...", filename);
}

// 初始化歌曲管理器
void init_playlist_manager(PlaylistManager* manager){
    manager->head = NULL;
    manager->tail = NULL;
    manager->current = NULL;
    manager->song_count = 0;
}

// 从文件读取数据构建双链表
int load_songs_from_file(PlaylistManager* manager, const char* filename) {
    return 0;
}

// 1. 在列表末尾添加歌曲
void add_song(PlaylistManager* manager, const char* title, const char* artist, const char* filepath) {
    return;
}

// 2. 按歌名删除歌曲
int delete_song_by_title(PlaylistManager* manager, const char* title) {
    return 0;
}

// 3. 播放歌曲
int play_song_by_title(PlaylistManager* manager, const char* title){
    return 0;
}

// 4. 显示播放列表（顺序）
void display_playlist(PlaylistManager* manager) {
    return;
}

// 5. 显示播放列表（逆序）
void display_playlist_reverse(PlaylistManager* manager) {
    return;
}

// 6. 将播放列表保存到文件
int export_playlist(PlaylistManager* manager, const char* filename) {
    return 0;
}

// 7. 下一首歌
void next_song(PlaylistManager* manager) {
    return;
}

// 8. 上一首歌
void previous_song(PlaylistManager* manager) {
    return;
}

// 9. 随机播放歌曲（非必须）
int play_song_random(PlaylistManager* manager) {
    return 0;
}

// 10. 在指定位置插入歌曲（非必须）
int insert_song_at(PlaylistManager* manager, int position, const char* title, 
                   const char* artist, const char* filepath) {
    return 1;
}

// 12. 按歌曲名排序（非必须）
void sort_by_title(PlaylistManager* manager) {
    return;
}

// 清空播放列表函数
void clear_playlist(PlaylistManager* manager) {
    Song* current = manager->head;
    while (current != NULL) {
        Song* next = current->next;
        free(current);
        current = next;
    }
    init_playlist_manager(manager);
    printf("播放列表已清空\n");
}


void display_menu() {
    printf("\n");
    printf("歌曲播放管理器菜单\n");
    printf("==========================================\n");
    printf("1. 添加歌曲\n");
    printf("2. 删除歌曲 (按歌名)\n");
    printf("3. 播放歌曲 (按歌名)\n");
    printf("4. 显示播放列表 (顺序)\n");
    printf("5. 显示播放列表 (逆序)\n");
    printf("6. 导出歌单\n");
    printf("7. 切换到下一首歌\n");
    printf("8. 切换到上一首歌\n");
    printf("9. 随机播放歌曲(非必须)\n");
    printf("10. 在指定位置添加歌曲(非必须)\n");
    printf("11. 清空播放列表(非必须)\n");
    printf("12. 按歌曲名排序(非必须)\n");
    printf("0. 退出程序\n");
    printf("==========================================\n");
    printf("请选择选项 (0-12): ");
}

// 清空输入缓冲区
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 读取用户输入的字符串
void get_user_input(char* buffer, int size, const char* prompt) {
    printf("%s", prompt);
    fgets(buffer, size, stdin);

    // 去除换行符
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n') {
        buffer[len-1] = '\0';
    }
}

// 主程序 - 交互式界面
int main() {
    PlaylistManager manager;
    init_playlist_manager(&manager);
    load_songs_from_file(&manager,"song_list.txt");

    printf("=== 双链表歌曲播放管理器 ===\n");
    printf("已加载 %d 首歌曲\n", manager.song_count);
    manager.current = manager.head;
    int choice;
    char input[100];

    do {
        display_menu();

        if (scanf("%d", &choice) != 1) {
            printf("无效输入，请重新选择\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1: {                   // 添加歌曲
                char title[100], artist[50], filepath[300];
                float duration;

                get_user_input(title, sizeof(title), "请输入歌曲名: ");
                get_user_input(artist, sizeof(artist), "请输入歌手: ");
                get_user_input(filepath, sizeof(filepath), "请输入文件路径: ");
                clear_input_buffer();

                add_song(&manager, title, artist, filepath);
                break;
            }
            case 2: {                   // 删除歌曲 (按歌名)
                char title[100];
                get_user_input(title, sizeof(title), "请输入要删除的歌曲名称: ");
                int res = delete_song_by_title(&manager, title);
                break;
            }
            case 3: {                   // 播放歌曲（按歌名）
                char title[100];
                get_user_input(title, sizeof(title), "请输入要播放的歌曲名称: ");
                int res = play_song_by_title(&manager, title);
                break;
            }
            case 4: {                   // 显示播放列表（顺序）
                display_playlist(&manager);
                break;
            }
            case 5: {                   // 显示播放列表（逆序）
                display_playlist_reverse(&manager);
                break;
            }
            case 6: {                   // 导出播放列表
                char path2export[300];
                get_user_input(path2export, sizeof(path2export), "请输入要导出的目标文件名: ");
                int res = export_playlist(&manager, path2export);
                break;
            }
            case 7: {                   // 切换到下一首歌
                next_song(&manager);
                break;
            }
            case 8: {                   // 切换到上一首歌
                previous_song(&manager);
                break;
            }
            case 9: {                   // 随机播放歌曲(非必须)
                int res = play_song_random(&manager);
                break;
            }
            case 10: {                  // 在指定位置添加歌曲(非必须)
                char title[100], artist[50], filepath[300];
                int position;
                get_user_input(title, sizeof(title), "请输入歌曲名: ");
                get_user_input(artist, sizeof(artist), "请输入歌手: ");
                get_user_input(filepath, sizeof(filepath), "请输入文件路径: ");
                printf("请输入插入位置: ");
                scanf("%d", &position);
                insert_song_at(&manager, position, title, artist, filepath);
                break;
            }
            case 11: {                  // 清空播放列表(非必须)
                clear_playlist(&manager);
                break;
            }
            case 12: {                  // 按歌曲名排序(非必须)
                sort_by_title(&manager);
                break;
            }
            case 0: // 退出程序
                printf("感谢使用歌曲播放管理器!\n");
                break;
            default:
                printf("? 无效选择，请重新选择\n");
                break;
        }

        // 暂停让用户查看结果
        if (choice != 0) {
            printf("\n按回车键继续...");
            getchar();
        }

    } while (choice != 0);

    // 清理内存
    clear_playlist(&manager);

    return 0;
}