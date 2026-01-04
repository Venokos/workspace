#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// 歌曲节点结构体
typedef struct Song {
    int id;
    char title[100];
    char artist[50];
    char filepath[300];
    struct Song* next;
} Song;

// 播放列表管理器结构
typedef struct PlaylistManager{
    Song* head; // 头节点
    Song* tail; // 尾节点
    Song* current; // 当前播放歌曲
    int song_count;
} PlaylistManager;

// 函数声明
void init_playlist_manager(PlaylistManager* manager);                           // 初始化管理器
int load_songs_from_file(PlaylistManager* manager, const char* filename);       // 从文件中读取歌曲
void add_song(PlaylistManager* manager, const char* title, const char* artist,  // 手动添加歌曲
              const char* filepath);
void display_playlist(PlaylistManager* manager);                                // 显示播放列表
int delete_songs_by_title(PlaylistManager* manager, const char* title);         // 删除指定标题的歌曲
int play_song_by_title(PlaylistManager* manager, const char* title);            // 按标题播放歌曲
int export_playlist(PlaylistManager* manager, const char* filename);            // 导出播放列表
int play_song_random(PlaylistManager* manager);                                 // 随机播放歌曲
int insert_song_at(PlaylistManager* manager, int position, const char* title, const char* artist, const char* filepath);    // 在指定位置插入歌曲
void destroy_playlist(PlaylistManager* manager);                                // 销毁播放列表

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
}

// // Windows 版本
// void play_audio(const char* filename){
//     char command[256];
//     FILE *mp3File = fopen(filename, "rb");
//     if (!mp3File) {
//         printf("无法打开文件 %s\n", filename);
//         return;
//     }
//     else{
//         printf("Found File!!");
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

// 从文件读取数据
int load_songs_from_file(PlaylistManager* manager, const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) return -1;

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


// 初始化歌曲管理器
void init_playlist_manager(PlaylistManager* manager){
    manager->head = NULL;
    manager->tail = NULL;
    manager->current = NULL;
    manager->song_count = 0;
}

// 1. 在列表末尾添加歌曲
void add_song(PlaylistManager* manager, const char* title, const char* artist, 
              const char* filepath) {
    Song* newSong = (Song*)malloc(sizeof(Song));
    if (newSong == NULL) {
        printf("内存分配失败！\n");
        exit(-1);
    }
    strcpy(newSong->title, title);
    strcpy(newSong->artist, artist);
    strcpy(newSong->filepath, filepath);
    newSong->next = NULL;
    // 如果链表为空
    if (manager->head == NULL) {
        manager->head = newSong;
        manager->current = newSong;
        manager->tail = newSong;    
        newSong->id = 1;
        manager->song_count++;
    }
    else {
        manager->tail->next = newSong;
        manager->tail = newSong;
        manager->song_count++;
        newSong->id = manager->song_count;
    }
    return;
}

// 2. 显示播放列表
void display_playlist(PlaylistManager* manager) {
    int count = 0;
    Song* temp = manager->head;
    printf("播放列表（%d首歌曲）\n", manager->song_count);
    printf("==========================================\n");
    while (temp != NULL) {
        count++;
        printf("%d. %s\t- %s\t(%s)\n", temp->id, temp->title, 
            temp->artist, temp->filepath);
        temp = temp->next;  
    }
    return;
}

// 3. 删除歌曲
int delete_songs_by_title(PlaylistManager* manager, const char* title) {
    Song* temp = manager->head;
    Song* prior = NULL; // 保存当前节点的前驱
    while (temp != NULL && strcmp(temp->title, title) != 0) {
        prior = temp;
        temp = temp->next;
    }
    // 如果没找到
    if (temp == NULL) {
        printf("未找到歌曲！\n");
        return -1;
    }
    // 如果删除的是头节点
    else if (temp == manager->head) {
        manager->head = temp->next;
        printf("已删除歌曲： %s - %s (path: %s)", temp->artist, 
            temp->title, temp->filepath);
        free(temp);
        manager->song_count--;
        // 修改歌曲id
        temp = manager->head;
        while (temp != NULL) {
            temp->id--;
            temp = temp->next;
        }
    }
    // 其他一般情况
    else {
        prior->next = prior->next->next;
        printf("已删除歌曲： %s - %s (path: %s)", temp->artist, 
            temp->title, temp->filepath);
        free(temp);

        // 修改歌曲id
        temp = prior->next;
        while (temp != NULL) {
            temp->id--;
            temp = temp->next;
        }

        manager->song_count--;
    }
    return 0;
}

// 4. 播放歌曲
int play_song_by_title(PlaylistManager* manager, const char* title) {
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

// 5. 将播放列表保存到文件
int export_playlist(PlaylistManager* manager, const char* filename) {
    FILE* destination = fopen(filename, "a");
    if (destination == NULL) return -1;

    Song* temp = manager->head;

    while (temp != NULL) {
        fprintf(destination, "%s,%s,%s\n", temp->title, 
            temp->artist, temp->filepath);
        temp = temp->next; 
    }

    fclose(destination);
    return 0;
}

// 6. 随机播放歌曲（非必须）
int play_song_random(PlaylistManager* manager) {
    // 设置随机数种子（使用当前时间）
    srand(time(NULL));
    // 生成0~(song_count-1)的随机整数
    int random_num = rand() % manager->song_count;
    manager->current = manager->head;
    int i = 0;
    while (i < random_num) {
        i++;
        manager->current = manager->current->next;
    }
    if (manager->current == NULL) {
        printf("Error!\n");
        return -1;
    }
    play_audio(manager->current->filepath);
    return 0;
}

// 7. 在指定位置插入歌曲（非必须）
int insert_song_at(PlaylistManager* manager, int position, const char* title, 
                   const char* artist, const char* filepath) {
    if (position <= 0) {
        printf("Wrong position!\n");
        return -1;
    }
    
    Song* newSong = (Song*)malloc(sizeof(Song));
    Song* prior = NULL;
    Song* temp = manager->head;
    if (newSong == NULL) {
        printf("内存分配失败！\n");
        exit(-1);
    }
    strcpy(newSong->title, title);
    strcpy(newSong->artist, artist);
    strcpy(newSong->filepath, filepath);
    newSong->next = NULL;
    // 如果是空链表
    if (manager->song_count == 0) {
        if (position == 1) {
            add_song(manager, title, artist, filepath);
            // 修改歌曲id
            temp = manager->head->next;
            while (temp != NULL) {
                temp->id++;
                temp = temp->next;
            }
        }
        else {
            printf("Wrong position!\n");
            return -1;
        }
    }
    // 如果不是空链表且插入在第一个
    else if (position == 1) {
        newSong->next = manager->head;
        manager->head = newSong;
        newSong->id = 1;
        manager->song_count++;
        // 修改歌曲id
        temp = manager->head->next;
        while (temp != NULL) {
            temp->id++;
            temp = temp->next;
        }
    }
    // 其他一般情况
    else {
        int i = 1;
        prior = manager->head;
        while (i < position - 1) {      
            prior = prior->next;
            i++;
            if (prior == NULL) {
                printf("Wrong position!\n");
                return -1;
            }
        }
        newSong->next = prior->next;
        prior->next = newSong;  

        newSong->id = position;
        manager->song_count++;
        // 修改歌曲id
        temp = newSong->next;
        while (temp != NULL) {
            temp->id++;
            temp = temp->next;
        }
    }
    return 0;
}

// 8. 清空播放列表（非必须）
void destroy_playlist(PlaylistManager* manager) {
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
    printf("1. 手动添加歌曲\n");
    printf("2. 显示播放列表\n");
    printf("3. 删除歌曲 (按歌名)\n");
    printf("4. 播放歌曲 (按歌名)\n");
    printf("5. 导出歌单\n");
    printf("6. 随机播放歌曲(非必须)\n");
    printf("7. 在指定位置添加歌曲(非必须)\n");
    printf("8. 清空播放列表(非必须)\n");
    printf("0. 退出程序\n");
    printf("==========================================\n");
    printf("请选择选项 (0-8): ");
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

    printf("=== 歌曲播放管理器 ===\n");
    printf("已加载 %d 首歌曲\n", manager.song_count);

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
            case 1: {               // 添加歌曲
                char title[100], artist[50], filepath[300];
                float duration;

                get_user_input(title, sizeof(title), "请输入歌曲名: ");
                get_user_input(artist, sizeof(artist), "请输入歌手: ");
                get_user_input(filepath, sizeof(filepath), "请输入文件路径: ");
                clear_input_buffer();

                add_song(&manager, title, artist, filepath);
                break;
            }
            case 2:{                // 显示播放列表 (必须)
                display_playlist(&manager);
                break;
            }
            case 3: {               // 删除歌曲 (必须)
                char title[100];
                get_user_input(title, sizeof(title), "请输入要删除的歌曲名称: ");
                delete_songs_by_title(&manager, title);
                break;
            }
            case 4: {                 // 按歌名播放歌曲
                char title[100];
                get_user_input(title, sizeof(title), "请输入要播放的歌曲名称: ");
                int res = play_song_by_title(&manager, title);
                break;
            }
            case 5: {
                char path2export[300];
                get_user_input(path2export, sizeof(path2export), "请输入要导出的目标文件名: ");
                export_playlist(&manager, path2export);
                break;
            }
            case 6: {
                play_song_random(&manager);
                break;
            }
            case 7: {
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
            case 8: {
                destroy_playlist(&manager);
                break;
            }
            case 0: // 退出程序
                printf("感谢使用歌曲播放管理器!\n");
                break;

            default:
                printf("无效选择，请重新选择\n");
                break;
        }

        // 暂停让用户查看结果
        if (choice != 0) {
            printf("\n按回车键继续...");
            getchar();
        }

    } while (choice != 0);

    // 清理内存
    destroy_playlist(&manager);

    return 0;
}