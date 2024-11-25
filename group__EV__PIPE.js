var group__EV__PIPE =
[
    [ "ev_ipc_frame_hdr", "group__EV__PIPE.html#structev__ipc__frame__hdr", [
      [ "hdr_dtsz", "group__EV__PIPE.html#a36dbdb07201f7e55fc8856afccb1ce13", null ],
      [ "hdr_exsz", "group__EV__PIPE.html#aed0dee7159ebc97006238b444a14bd5f", null ],
      [ "hdr_flags", "group__EV__PIPE.html#a7a5881c9c7a7bda5fe6c7ffb84283576", null ],
      [ "hdr_magic", "group__EV__PIPE.html#a5ebbcb3d4fd7bd6b00c729c74bf94e69", null ],
      [ "hdr_version", "group__EV__PIPE.html#ae261a6c76df474661a96b8fcccfada63", null ],
      [ "reserved", "group__EV__PIPE.html#aa43c4c21b173ada1b6b7568956f0d650", null ]
    ] ],
    [ "ev_pipe", "group__EV__PIPE.html#structev__pipe", [
      [ "ev_pipe_backend", "group__EV__PIPE.html#unionev__pipe_1_1ev__pipe__backend", [
        [ "_useless", "group__EV__PIPE.html#a3254ed812313bfe9cbcf7a7982d69cad", null ]
      ] ],
      [ "ev_pipe_backend.data_mode", "group__EV__PIPE.html#structev__pipe_1_1ev__pipe__backend_8data__mode", [
        [ "stream", "group__EV__PIPE.html#af7b44cfafd5c52223d5498196c8a2e7b", null ]
      ] ],
      [ "ev_pipe_backend.ipc_mode", "group__EV__PIPE.html#structev__pipe_1_1ev__pipe__backend_8ipc__mode", [
        [ "io", "group__EV__PIPE.html#af98ed07a4d5f50f7de1410d905f1477f", null ]
      ] ],
      [ "ev_pipe_backend.ipc_mode.mask", "group__EV__PIPE.html#structev__pipe_1_1ev__pipe__backend_8ipc__mode_8mask", [
        [ "no_cmsg_cloexec", "group__EV__PIPE.html#ac58e82727c3e3b7505a424ac514584ec", null ],
        [ "rio_pending", "group__EV__PIPE.html#a4e809c3bcc760d4b1c1b57ce96621dc5", null ],
        [ "wio_pending", "group__EV__PIPE.html#ac9fedaf0434b88b979ca3c27c67082ae", null ]
      ] ],
      [ "ev_pipe_backend.ipc_mode.rio", "group__EV__PIPE.html#structev__pipe_1_1ev__pipe__backend_8ipc__mode_8rio", [
        [ "rqueue", "group__EV__PIPE.html#a7b3a7639696357427c3ca24db9d79176", null ]
      ] ],
      [ "ev_pipe_backend.ipc_mode.rio.curr", "group__EV__PIPE.html#structev__pipe_1_1ev__pipe__backend_8ipc__mode_8rio_8curr", [
        [ "buf_idx", "group__EV__PIPE.html#a5e17f37a125d6dc12c2723524b6aa5de", null ],
        [ "buf_pos", "group__EV__PIPE.html#a6474edcef06ccadbded6430abdc30f7e", null ],
        [ "data_remain_size", "group__EV__PIPE.html#a3382edeaaa84392c783f5df3b1d57df1", null ],
        [ "head_read_size", "group__EV__PIPE.html#af978a8c4c24a50ef16b18c093c2a5bcb", null ],
        [ "reading", "group__EV__PIPE.html#aeceadc1d40cea061fd5986f2a109ee93", null ]
      ] ],
      [ "ev_pipe_backend.ipc_mode.wio", "group__EV__PIPE.html#structev__pipe_1_1ev__pipe__backend_8ipc__mode_8wio", [
        [ "wqueue", "group__EV__PIPE.html#a15bf34c2a3b6fe18e68371e6139b565f", null ]
      ] ],
      [ "ev_pipe_backend.ipc_mode.wio.curr", "group__EV__PIPE.html#structev__pipe_1_1ev__pipe__backend_8ipc__mode_8wio_8curr", [
        [ "buf_idx", "group__EV__PIPE.html#a5e17f37a125d6dc12c2723524b6aa5de", null ],
        [ "buf_pos", "group__EV__PIPE.html#a6474edcef06ccadbded6430abdc30f7e", null ],
        [ "head_send_capacity", "group__EV__PIPE.html#acaeb411334afc5c233cd77cba4c4e50b", null ],
        [ "head_send_size", "group__EV__PIPE.html#a796751d2618771172d1b291bca8b3abe", null ],
        [ "writing", "group__EV__PIPE.html#a1cea5345d284f36245a94301b114b27c", null ]
      ] ],
      [ "backend", "group__EV__PIPE.html#a82580aaabfdbb9ee8f60caae44b6d759", null ],
      [ "base", "group__EV__PIPE.html#a0eb53837eb049ab9bfb987bdc03c7fe4", null ],
      [ "close_cb", "group__EV__PIPE.html#a4e755ac1e82872532714ce8767cfebf8", null ],
      [ "pipfd", "group__EV__PIPE.html#aef9634d2dc5610d83ebfb27fa2ec2c33", null ]
    ] ],
    [ "ev_pipe_write_req", "group__EV__PIPE.html#structev__pipe__write__req", [
      [ "ev_pipe_write_backend", "group__EV__PIPE.html#structev__pipe__write__req_1_1ev__pipe__write__backend", [
        [ "_useless", "group__EV__PIPE.html#a7950fb56ade1c27b65c87ee2b164e7a4", null ]
      ] ],
      [ "backend", "group__EV__PIPE.html#a313762a9028276cd9c8c2a6a57d45450", null ],
      [ "base", "group__EV__PIPE.html#ab32a6671103c22b028b4346a3a19a7cd", null ],
      [ "ucb", "group__EV__PIPE.html#a5c06465a1deae59dffe1ec1068cf8d18", null ]
    ] ],
    [ "ev_pipe_read_req", "group__EV__PIPE.html#structev__pipe__read__req", [
      [ "ev_pipe_read_backend", "group__EV__PIPE.html#structev__pipe__read__req_1_1ev__pipe__read__backend", [
        [ "_useless", "group__EV__PIPE.html#a7950fb56ade1c27b65c87ee2b164e7a4", null ]
      ] ],
      [ "backend", "group__EV__PIPE.html#a590918e0967690af6e5ff80a78882153", null ],
      [ "base", "group__EV__PIPE.html#a1f6e55732353ecffa3d17d537b435682", null ],
      [ "ucb", "group__EV__PIPE.html#a67845ac671fc7af32baee772d3f18740", null ]
    ] ],
    [ "ev_pipe_write_req.handle", "group__EV__PIPE.html#structev__pipe__write__req_8handle", [
      [ "role", "group__EV__PIPE.html#a29a7e96467b69a9f5a93332e29e9b0de", null ]
    ] ],
    [ "ev_pipe_write_req.handle.u", "group__EV__PIPE.html#unionev__pipe__write__req_8handle_8u", [
      [ "os_socket", "group__EV__PIPE.html#a5f87c1225d0ad9b7251c464f18fb7fad", null ]
    ] ],
    [ "ev_pipe_read_req.handle", "group__EV__PIPE.html#structev__pipe__read__req_8handle", [
      [ "os_socket", "group__EV__PIPE.html#a5f87c1225d0ad9b7251c464f18fb7fad", null ]
    ] ],
    [ "EV_PIPE_INVALID", "group__EV__PIPE.html#ga89d4f70c9692f5311cb04cae3036a217", null ],
    [ "ev_ipc_frame_hdr_t", "group__EV__PIPE.html#ga7c85e8d9dd7916a5ed45f3d9f4da40c7", null ],
    [ "ev_pipe_cb", "group__EV__PIPE.html#ga686dd5be730f1175e4c5a38874ff21aa", null ],
    [ "ev_pipe_flags_t", "group__EV__PIPE.html#gabb1a28215db6a40815275a69815f4bd9", null ],
    [ "ev_pipe_read_cb", "group__EV__PIPE.html#ga8b6580cfd6ac1c624dea5c1391fa931f", null ],
    [ "ev_pipe_read_req_t", "group__EV__PIPE.html#ga2ca91b8051b90feb9019c54ac4e240c2", null ],
    [ "ev_pipe_t", "group__EV__PIPE.html#ga2c8e3d7aa31e2818cb82241092ec761e", null ],
    [ "ev_pipe_write_cb", "group__EV__PIPE.html#gae6a2bdc18176cfa900ed4850060b6605", null ],
    [ "ev_pipe_write_req_t", "group__EV__PIPE.html#ga516d2510ca1a7943726375bf0ec90d2f", null ],
    [ "ev_pipe_flags_e", "group__EV__PIPE.html#ga4f88ede6fed902d8d7718273b31c91f7", [
      [ "EV_PIPE_READABLE", "group__EV__PIPE.html#gga4f88ede6fed902d8d7718273b31c91f7abbb4d8d522f315c16cbd8af0bd45bfcd", null ],
      [ "EV_PIPE_WRITABLE", "group__EV__PIPE.html#gga4f88ede6fed902d8d7718273b31c91f7a46f79cfd387d32e1b4739de7762725dd", null ],
      [ "EV_PIPE_NONBLOCK", "group__EV__PIPE.html#gga4f88ede6fed902d8d7718273b31c91f7a7976c8e8ed55d5d7f86ae368aac2d044", null ],
      [ "EV_PIPE_IPC", "group__EV__PIPE.html#gga4f88ede6fed902d8d7718273b31c91f7ac9b05825045b4efb624e2ecfc37dc754", null ]
    ] ],
    [ "ev_pipe_accept", "group__EV__PIPE.html#ga0992a8957c47c4bb9eaea9ea7fac4d71", null ],
    [ "ev_pipe_close", "group__EV__PIPE.html#ga533fa9d645f0aefb1ce6c9ed94208ae4", null ],
    [ "ev_pipe_exit", "group__EV__PIPE.html#ga7a7a2bba0a2ef669bff6f1294801e8bb", null ],
    [ "ev_pipe_init", "group__EV__PIPE.html#ga2c7ffb1ee536cf32262a106e2e0d57fc", null ],
    [ "ev_pipe_make", "group__EV__PIPE.html#gaae75ef658b6c90b6e535061cd1be392c", null ],
    [ "ev_pipe_open", "group__EV__PIPE.html#ga8d6556b6a8ac6cfcb60ab5d72c613d1a", null ],
    [ "ev_pipe_read", "group__EV__PIPE.html#ga02248b3a52b15317241a7f9efa0e29ba", null ],
    [ "ev_pipe_write", "group__EV__PIPE.html#ga0a81355f8f5d19cac80bf0463709424a", null ],
    [ "ev_pipe_write_ex", "group__EV__PIPE.html#gabbaec69bc181c43558004d1d5f9d4bd6", null ]
];