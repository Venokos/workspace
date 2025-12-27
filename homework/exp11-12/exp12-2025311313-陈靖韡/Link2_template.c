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


// linux 版本
void play_audio(const char* filename) {
    char command[256];
    FILE *mp3File = fopen(filename, "rb");
    if (!mp3File) {
        printf("无法打开文件 %s\n", filename);
        return;
    }
    else{
        printf("Found File!!\n");
    }
    snprintf(command, sizeof(command), "xdg-open \"%s\" &", filename);
    int ret = system(command);
    if (ret != 0) {
        printf("播放失败或中断，检查文件格式是否支持。\n");
    }
    printf("Playing %s ...", filename);
}

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


// 初始化歌曲管理器
void init_playlist_manager(PlaylistManager* manager){
    manager->head = NULL;
    manager->tail = NULL;
    manager->current = NULL; // 正在播放的歌曲
    manager->song_count = 0;
}

// 从文件读取数据构建双链表
int load_songs_from_file(PlaylistManager* manager, const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        return -1;
    }
    char line[500];

    while (fgets(line, sizeof(line), fp) != NULL) {
        // 移除行末换行符
        line[strcspn(line, "\n")] = 0;
        char title[100], artist[50], filepath[300];
        if (sscanf(line, "%99[^,],%49[^,],%299s", title, artist, filepath) == 3) {
            add_song(manager, title, artist, filepath);
        }

    }
    fclose(fp);
    return 0;
}

// 1. 在列表末尾添加歌曲
void add_song(PlaylistManager* manager, const char* title, const char* artist, 
              const char* filepath) {
    Song* newSong = (Song*)malloc(sizeof(Song));
    strcpy(newSong->title, title);
    strcpy(newSong->artist, artist);
    strcpy(newSong->filepath, filepath);
    newSong->next = NULL;
    // 如果链表为空
    if (manager->head == NULL) {
        newSong->prev = NULL;
        manager->head = newSong;
        manager->tail = newSong;    
    }
    else {
        manager->tail->next = newSong;
        newSong->prev = manager->tail;
        manager->tail = newSong;
    }
    manager->song_count++;
    return;
}


// 2. 按歌名删除歌曲
int delete_song_by_title(PlaylistManager* manager, const char* title) {
    Song* temp = manager->head;
    while (temp != NULL && strcmp(temp->title, title) != 0) {
        temp = temp->next;
    }
    // 如果没找到
    if (temp == NULL) {
        printf("未找到歌曲！\n");
        return -1;
    }
    // 如果删除的是头节点
    else if (temp == manager->head) {
        manager->head = manager->current->next;
        printf("已删除歌曲： %s - %s (path: %s)", temp->artist, 
            temp->title, temp->filepath);
        free(temp);
    }
    // 其他一般情况
    else {
        temp->prev = temp->next;
        printf("已删除歌曲： %s - %s (path: %s)", temp->artist, 
            temp->title, temp->filepath);
        free(temp);
    }
    manager->song_count--;
    return 0;
}

// 3. 播放歌曲
int play_song_by_title(PlaylistManager* manager, const char* title){
    manager->current = manager->head;
    while (manager->current != NULL && strcmp(manager->current->title, title) != 0) {
        manager->current = manager->current->next;  
    }
    // 如果没找到
    if (manager->current == NULL) {
        printf("未找到歌曲！\n");
        return -1;
    }
    else {
        play_audio(manager->current->filepath);
        printf("已播放标题为“%s”的歌曲\n", manager->current->title);
    }
    return 0;
}

// 4. 显示播放列表（顺序）
void display_playlist(PlaylistManager* manager) {
    int count = 0;
    Song* temp = manager->head;
    printf("播放列表（%d首歌曲）\n", manager->song_count);
    printf("==========================================\n");
    while (temp != NULL) {
        count++;
        printf("%d. %s\t- %s\t(%s)\n", count, temp->title, 
            temp->artist, temp->filepath);
        temp = temp->next;  
    }
    return;
}

// 5. 显示播放列表（逆序）
void display_playlist_reverse(PlaylistManager* manager) {
    int count = manager->song_count + 1;
    Song* temp = manager->tail;
    printf("播放列表（%d首歌曲）\n", manager->song_count);
    printf("==========================================\n");
    while (temp != NULL) {
        count--;
        printf("%d. %s\t- %s\t(%s)\n", count, temp->title, 
            temp->artist, temp->filepath);
        temp = temp->prev;  
    }
    return;
}

// 6. 将播放列表保存到文件
int export_playlist(PlaylistManager* manager, const char* filename) {
    FILE* destination = fopen(filename, "a");
    if (destination == NULL) return -1;

    Song* temp = manager->head;
    int count = 0;

    while (temp != NULL) {
        count++;
        fprintf(destination, "%s,%s,%s\n", temp->title, 
            temp->artist, temp->filepath);
        temp = temp->next; 
    }

    fclose(destination);
    return 0;
}

// 7. 下一首歌
void next_song(PlaylistManager* manager) {
    // 如果已经是最后一首歌
    if (manager->current == manager->tail) {
        printf("已是最后一首歌，即将播放第一首歌...\n");
        manager->current = manager->head;
    }
    else {
        manager->current = manager->current->next;
    }
    // 错误情况处理，防止非法内存访问
    if (manager->current == NULL) {
        printf("切换歌曲失败！\n");
        exit(-1);
    }
    play_audio(manager->current->filepath);
    return;
}

// 8. 上一首歌
void previous_song(PlaylistManager* manager) {
    // 如果是第一首歌
    if (manager->current == manager->head) {
        printf("已是第一首歌，即将播放最后一首歌...\n");
        manager->current = manager->tail;
    }
    else {
        manager->current = manager->current->prev;
    }
    // 错误情况处理，防止非法内存访问
    if (manager->current == NULL) {
        printf("切换歌曲失败！\n");
        exit(-1);
    }
    play_audio(manager->current->filepath);
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