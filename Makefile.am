ACLOCAL_AMFLAGS = -I m4
lib_LTLIBRARIES = \
	libyarn.la 

AM_CFLAGS=-I${top_srcdir} -I${top_srcdir}/src -I${top_srcdir}/proto -I${top_srcdir}/proto/server

libyarn_la_SOURCES = \
	proto/GetUserMappingsProtocol.pb-c.c \
	proto/HAServiceProtocol.pb-c.c \
	proto/HAZKInfo.pb-c.c \
	proto/IpcConnectionContext.pb-c.c \
	proto/JournalProtocol.pb-c.c \
	proto/LocalizationProtocol.pb-c.c \
	proto/ProtobufRpcEngine.pb-c.c \
	proto/ProtocolInfo.pb-c.c \
	proto/RefreshAuthorizationPolicyProtocol.pb-c.c \
	proto/RefreshUserMappingsProtocol.pb-c.c \
	proto/ResourceTracker.pb-c.c \
	proto/RpcHeader.pb-c.c \
	proto/Security.pb-c.c \
	proto/ZKFCProtocol.pb-c.c \
	proto/applicationclient_protocol.pb-c.c \
	proto/applicationmaster_protocol.pb-c.c \
	proto/containermanagement_protocol.pb-c.c \
	proto/resourcemanager_administration_protocol.pb-c.c \
	proto/yarn_protos.pb-c.c \
	proto/yarn_server_common_protos.pb-c.c \
	proto/yarn_server_common_service_protos.pb-c.c \
	proto/yarn_server_nodemanager_service_protos.pb-c.c \
	proto/yarn_service_protos.pb-c.c \
	proto/server/yarn_server_resourcemanager_service_protos.pb-c.c 

#	src/client_rm_protocol_impl.c \
#	src/hadoop_rpc.c \
#	src/hadoop_rpc_utils.c \
#	src/am_rm_protocol_impl.c \
#	src/container_manager_impl.c \
#	src/net_utils.c \
#	src/pbc_utils.c \
#	src/str_utils.c \
#
