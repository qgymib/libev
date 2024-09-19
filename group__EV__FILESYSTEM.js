var group__EV__FILESYSTEM =
[
    [ "ev_file_s", "group__EV__FILESYSTEM.html#structev__file__s", [
      [ "base", "group__EV__FILESYSTEM.html#a0eb53837eb049ab9bfb987bdc03c7fe4", null ],
      [ "close_cb", "group__EV__FILESYSTEM.html#addd4d03933d2b3ad42afc5b9fc63ccab", null ],
      [ "file", "group__EV__FILESYSTEM.html#a112af2907a5080b76afd091cdcfe880b", null ],
      [ "work_queue", "group__EV__FILESYSTEM.html#a704638632b2f84b7edbd65475714af37", null ]
    ] ],
    [ "ev_file_map", "group__EV__FILESYSTEM.html#structev__file__map", [
      [ "addr", "group__EV__FILESYSTEM.html#ae5bd6c22dbf0f6b5b0ae0233f8eb3704", null ],
      [ "backend", "group__EV__FILESYSTEM.html#a5a54be94abc55672ff4b1e33e60700d5", null ],
      [ "size", "group__EV__FILESYSTEM.html#af931a8871310b4dad23f0f0b0f623560", null ]
    ] ],
    [ "ev_fs_stat_s", "group__EV__FILESYSTEM.html#structev__fs__stat__s", [
      [ "st_atim", "group__EV__FILESYSTEM.html#a091257f26851140458b4d4c2dfb2beeb", null ],
      [ "st_birthtim", "group__EV__FILESYSTEM.html#aab97a1e647196b5ac8a46764b01a7224", null ],
      [ "st_blksize", "group__EV__FILESYSTEM.html#adb9252bb3343471e4aaaf7bf7df5363a", null ],
      [ "st_blocks", "group__EV__FILESYSTEM.html#a72c24b54949be7eaac849d71fc056a3c", null ],
      [ "st_ctim", "group__EV__FILESYSTEM.html#a24d4bc66f6d41ade09776ae461725baf", null ],
      [ "st_dev", "group__EV__FILESYSTEM.html#a0146849d3da5c91d9776888b14b82dcc", null ],
      [ "st_flags", "group__EV__FILESYSTEM.html#a513d310cddd83b8f1678cf2a8ca16714", null ],
      [ "st_gen", "group__EV__FILESYSTEM.html#a67c4e0f707b80853bb37d589136c00f0", null ],
      [ "st_gid", "group__EV__FILESYSTEM.html#a09c579712d49de2a34f3ec9d7fdaa850", null ],
      [ "st_ino", "group__EV__FILESYSTEM.html#abb54f0e7d91659ba9f4ab77a5392c08a", null ],
      [ "st_mode", "group__EV__FILESYSTEM.html#a5b4e70e604ddbe3fff52f27f9fb3df88", null ],
      [ "st_mtim", "group__EV__FILESYSTEM.html#aca174ee97c6451a15c5582a4d5fdf4c7", null ],
      [ "st_nlink", "group__EV__FILESYSTEM.html#abef7057bf9bf605a14cd64d34cf3424d", null ],
      [ "st_rdev", "group__EV__FILESYSTEM.html#ac430407fd3b0e421da1ee8f66c95a786", null ],
      [ "st_size", "group__EV__FILESYSTEM.html#ae9a97f03571901a066d512b87bc36dba", null ],
      [ "st_uid", "group__EV__FILESYSTEM.html#aa5d3e5f4a119ff845649c779062ce1f3", null ]
    ] ],
    [ "ev_dirent_s", "group__EV__FILESYSTEM.html#structev__dirent__s", [
      [ "name", "group__EV__FILESYSTEM.html#a5ac083a645d964373f022d03df4849c8", null ],
      [ "type", "group__EV__FILESYSTEM.html#a4de355e2721ef8c23c93565f769ec766", null ]
    ] ],
    [ "ev_fs_req_s", "group__EV__FILESYSTEM.html#structev__fs__req__s", [
      [ "cb", "group__EV__FILESYSTEM.html#acde35845b6beb81e961d74e0425a1782", null ],
      [ "file", "group__EV__FILESYSTEM.html#aa2f6cc8a3a5f576a58fa400ea657c818", null ],
      [ "node", "group__EV__FILESYSTEM.html#aad11ebad3f26bf69a1bb5968fc63a247", null ],
      [ "req_type", "group__EV__FILESYSTEM.html#a458d84a24881aec99a6c65ab36ba02ae", null ],
      [ "result", "group__EV__FILESYSTEM.html#af6a35d8bda2bbb2656b29287230d8c81", null ],
      [ "work_token", "group__EV__FILESYSTEM.html#a5db00589ff7f1564f3d299745e8e9e04", null ]
    ] ],
    [ "ev_fs_req_s.req", "group__EV__FILESYSTEM.html#unionev__fs__req__s_8req", null ],
    [ "ev_fs_req_s.req.as_open", "group__EV__FILESYSTEM.html#structev__fs__req__s_8req_8as__open", [
      [ "flags", "group__EV__FILESYSTEM.html#a4e5868d676cb634aa75b125a0f741abf", null ],
      [ "mode", "group__EV__FILESYSTEM.html#a15d61712450a686a7f365adf4fef581f", null ],
      [ "path", "group__EV__FILESYSTEM.html#ad6fe1d0be6347b8ef2427fa629c04485", null ]
    ] ],
    [ "ev_fs_req_s.req.as_seek", "group__EV__FILESYSTEM.html#structev__fs__req__s_8req_8as__seek", [
      [ "offset", "group__EV__FILESYSTEM.html#a7a86c157ee9713c34fbd7a1ee40f0c5a", null ],
      [ "whence", "group__EV__FILESYSTEM.html#a02c86cc535151887678873a6d0a3c347", null ]
    ] ],
    [ "ev_fs_req_s.req.as_read", "group__EV__FILESYSTEM.html#structev__fs__req__s_8req_8as__read", [
      [ "offset", "group__EV__FILESYSTEM.html#a7a86c157ee9713c34fbd7a1ee40f0c5a", null ],
      [ "read_req", "group__EV__FILESYSTEM.html#ae8eb0e5f5e1a3d35b49f7beda5ab5269", null ]
    ] ],
    [ "ev_fs_req_s.req.as_write", "group__EV__FILESYSTEM.html#structev__fs__req__s_8req_8as__write", [
      [ "offset", "group__EV__FILESYSTEM.html#a7a86c157ee9713c34fbd7a1ee40f0c5a", null ],
      [ "write_req", "group__EV__FILESYSTEM.html#a100a30494c229182e15617ee3f4db7c4", null ]
    ] ],
    [ "ev_fs_req_s.req.as_readdir", "group__EV__FILESYSTEM.html#structev__fs__req__s_8req_8as__readdir", [
      [ "path", "group__EV__FILESYSTEM.html#ad6fe1d0be6347b8ef2427fa629c04485", null ]
    ] ],
    [ "ev_fs_req_s.req.as_readfile", "group__EV__FILESYSTEM.html#structev__fs__req__s_8req_8as__readfile", [
      [ "path", "group__EV__FILESYSTEM.html#ad6fe1d0be6347b8ef2427fa629c04485", null ]
    ] ],
    [ "ev_fs_req_s.req.as_mkdir", "group__EV__FILESYSTEM.html#structev__fs__req__s_8req_8as__mkdir", [
      [ "mode", "group__EV__FILESYSTEM.html#a15d61712450a686a7f365adf4fef581f", null ],
      [ "path", "group__EV__FILESYSTEM.html#ad6fe1d0be6347b8ef2427fa629c04485", null ]
    ] ],
    [ "ev_fs_req_s.req.as_remove", "group__EV__FILESYSTEM.html#structev__fs__req__s_8req_8as__remove", [
      [ "path", "group__EV__FILESYSTEM.html#ad6fe1d0be6347b8ef2427fa629c04485", null ],
      [ "recursion", "group__EV__FILESYSTEM.html#af8532b6380228945d474f37fb6cdac27", null ]
    ] ],
    [ "ev_fs_req_s.rsp", "group__EV__FILESYSTEM.html#unionev__fs__req__s_8rsp", [
      [ "dirents", "group__EV__FILESYSTEM.html#a7b84e17e8248bdb3177a4a8f4ddde025", null ],
      [ "filecontent", "group__EV__FILESYSTEM.html#a86c0460e2f881850a75eac2f5e0b7d07", null ],
      [ "stat", "group__EV__FILESYSTEM.html#a77ddcb5f19832f4145345889013ab3a4", null ]
    ] ],
    [ "EV_FS_O_APPEND", "group__EV__FILESYSTEM.html#ga6b87035fc5a60114b06c65634192673c", null ],
    [ "EV_FS_O_CREAT", "group__EV__FILESYSTEM.html#ga40753842998cf26c9d061a3c50a46d72", null ],
    [ "EV_FS_O_DSYNC", "group__EV__FILESYSTEM.html#gaaf03e736ed4e05fc270e6b9e35047cd6", null ],
    [ "EV_FS_O_EXCL", "group__EV__FILESYSTEM.html#gaf478b16e3f8b710364abd4d2253da3b2", null ],
    [ "EV_FS_O_RDONLY", "group__EV__FILESYSTEM.html#gade874295ce4119b4a34d76ca0ae2093d", null ],
    [ "EV_FS_O_RDWR", "group__EV__FILESYSTEM.html#ga2de44f882bf934fdb3ddacac182a1d04", null ],
    [ "EV_FS_O_SYNC", "group__EV__FILESYSTEM.html#gac8b45e8c79663ba0b4e6f4fdd071fb5d", null ],
    [ "EV_FS_O_TRUNC", "group__EV__FILESYSTEM.html#ga8d121ecbf303f41d903c4f819bb31958", null ],
    [ "EV_FS_O_WRONLY", "group__EV__FILESYSTEM.html#gabb3d73d08f2a5ab8242c966322ab2ae2", null ],
    [ "EV_FS_S_IRUSR", "group__EV__FILESYSTEM.html#gacc78e3d681a03ff5f60690f2532d345e", null ],
    [ "EV_FS_S_IRWXU", "group__EV__FILESYSTEM.html#ga58446f2238f8435a794c6e7ee88e6c88", null ],
    [ "EV_FS_S_IWUSR", "group__EV__FILESYSTEM.html#gaef2ebfd66e9c68477096598e7ef3bda5", null ],
    [ "EV_FS_S_IXUSR", "group__EV__FILESYSTEM.html#gacdf783a3867a5d0e747c5d729ade43eb", null ],
    [ "EV_FS_SEEK_BEG", "group__EV__FILESYSTEM.html#ga60896708a47a80a8c5968f2063a38360", null ],
    [ "EV_FS_SEEK_CUR", "group__EV__FILESYSTEM.html#gaed2681a4b983db2f303a46d688950ab2", null ],
    [ "EV_FS_SEEK_END", "group__EV__FILESYSTEM.html#ga677f9a736418a664f74dde7861eae056", null ],
    [ "EV_OS_FILE_INVALID", "group__EV__FILESYSTEM.html#gad516d9cef6cc019687a9b5b37e5ef232", null ],
    [ "ev_dirent_t", "group__EV__FILESYSTEM.html#ga6ae489a03f35fef172078c3ebf92c0bc", null ],
    [ "ev_dirent_type_t", "group__EV__FILESYSTEM.html#gaa77a55c2e681f26bdf07161a051a1ae4", null ],
    [ "ev_file_cb", "group__EV__FILESYSTEM.html#ga8c312226577eb01565d88736c67c460a", null ],
    [ "ev_file_close_cb", "group__EV__FILESYSTEM.html#gae06a9a4a1e14756c22d4c004a5ae5212", null ],
    [ "ev_file_t", "group__EV__FILESYSTEM.html#ga00c0feeb8883df5988360e0d3cbd43ef", null ],
    [ "ev_fs_req_t", "group__EV__FILESYSTEM.html#gae7a0c42ce306b94c5cfad60ed2a2a071", null ],
    [ "ev_fs_req_type_t", "group__EV__FILESYSTEM.html#ga69252665b0f487234753384bebc0c6a9", null ],
    [ "ev_fs_stat_t", "group__EV__FILESYSTEM.html#ga9a4729e0856a450f1e8ade5d8aaaf392", null ],
    [ "ev_os_file_t", "group__EV__FILESYSTEM.html#ga5b376c464c534b43cb74294e782775cc", null ],
    [ "ev_dirent_type_e", "group__EV__FILESYSTEM.html#gac45d90532510222c6012f2d2829b614a", null ],
    [ "ev_fs_req_type_e", "group__EV__FILESYSTEM.html#ga5e5305fef033f66213d8133028d7c069", null ],
    [ "ev_file_close", "group__EV__FILESYSTEM.html#ga6661a15501969fb4bf98395907fe64dd", null ],
    [ "ev_file_mmap", "group__EV__FILESYSTEM.html#gaae19d2b768e7c37fb7e692670fa3969f", null ],
    [ "ev_file_munmap", "group__EV__FILESYSTEM.html#gabf44c9b776740b3e31a72391fbb92496", null ],
    [ "ev_file_open", "group__EV__FILESYSTEM.html#ga8d98c74a59e2eca116cc2099c49163a8", null ],
    [ "ev_file_pread", "group__EV__FILESYSTEM.html#ga4ec4dd4fabe0e688fe052a5398de34f8", null ],
    [ "ev_file_preadv", "group__EV__FILESYSTEM.html#ga68561ad4d45f3f0357be11049215aab0", null ],
    [ "ev_file_pwrite", "group__EV__FILESYSTEM.html#ga0827eced0865923d2f0adc6b907c380f", null ],
    [ "ev_file_pwritev", "group__EV__FILESYSTEM.html#ga89f47c3391d24c019266906e1bb98cee", null ],
    [ "ev_file_read", "group__EV__FILESYSTEM.html#ga7d4902fa31767855eb4dd4467185527f", null ],
    [ "ev_file_readv", "group__EV__FILESYSTEM.html#ga580317988c22b44c8fad9677a2a8fa27", null ],
    [ "ev_file_seek", "group__EV__FILESYSTEM.html#ga4603c51a5147b385493409d993608880", null ],
    [ "ev_file_stat", "group__EV__FILESYSTEM.html#gaddbc2ef7ba997c6f0d83b262b467d2bc", null ],
    [ "ev_file_write", "group__EV__FILESYSTEM.html#gae2273f91b2142311d5859845e0c678b3", null ],
    [ "ev_file_writev", "group__EV__FILESYSTEM.html#gad278359f455b4d3b70a778a92eddd671", null ],
    [ "ev_fs_get_file", "group__EV__FILESYSTEM.html#ga1fd9fa7151d32540d48e2ddc17eb451c", null ],
    [ "ev_fs_get_filecontent", "group__EV__FILESYSTEM.html#ga4916fa1c4811f29a7adf925be01f64d0", null ],
    [ "ev_fs_get_first_dirent", "group__EV__FILESYSTEM.html#ga265a94727c5acb6e2e1b98a61f9f764a", null ],
    [ "ev_fs_get_next_dirent", "group__EV__FILESYSTEM.html#gae0effcf528b7da462127984c04a6feef", null ],
    [ "ev_fs_get_statbuf", "group__EV__FILESYSTEM.html#ga374491634c12dc97ab121c678239466a", null ],
    [ "ev_fs_mkdir", "group__EV__FILESYSTEM.html#ga0f703b2cb4998b62e91a63d03cd20e58", null ],
    [ "ev_fs_readdir", "group__EV__FILESYSTEM.html#ga4f9e1bc2ec78aefdfe9b84a9f57b7667", null ],
    [ "ev_fs_readfile", "group__EV__FILESYSTEM.html#gadfe3fc7451f0fdf4bc1f4151f100cb0b", null ],
    [ "ev_fs_remove", "group__EV__FILESYSTEM.html#gaf03eaa86cdd21cf62c4acc3eee4bf4a6", null ],
    [ "ev_fs_req_cleanup", "group__EV__FILESYSTEM.html#ga1290180ebee040edf3ce381d4b01a092", null ]
];