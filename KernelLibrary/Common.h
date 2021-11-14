#pragma once

enum class DataItemType : short {
	IrpArrived,
	IrpCompleted,
};

enum class IrpMajorCode :unsigned char {
	CREATE = 0x00,
	CREATE_NAMED_PIPE = 0x01,
	CLOSE = 0x02,
	READ = 0x03,
	WRITE = 0x04,
	QUERY_INFORMATION = 0x05,
	SET_INFORMATION = 0x06,
	QUERY_EA,
	SET_EA,
	FLUSH_BUFFERS,
	QUERY_VOLUME_INFORMATION,
	SET_VOLUME_INFORMATION,
	DIRECTORY_CONTROL,
	FILE_SYSTEM_CONTROL,
	DEVICE_CONTROL,
	INTERNAL_DEVICE_CONTROL,
	SHUTDOWN,
	LOCK_CONTROL,
	CLEANUP,
	CREATE_MAILSLOT,
	QUERY_SECURITY,
	SET_SECURITY,
	POWER,
	SYSTEM_CONTROL,
	DEVICE_CHANGE,
	QUERY_QUOTA,
	SET_QUOTA,
	PNP,
};

enum class IrpMinorCode :unsigned char {
	None =0,

	// PNP

	START_DEVICE = 0x00,
	QUERY_REMOVE_DEVICE = 0x01,
	REMOVE_DEVICE = 0x02,
	CANCEL_REMOVE_DEVICE = 0x03,
	STOP_DEVICE,
	QUERY_STOP_DEVICE,
	CANCEL_STOP_DEVICE,

	QUERY_DEVICE_RELATIONS,
	QUERY_INTERFACE,
	QUERY_CAPABLITIES,
	QUERY_RESOURCES,
	QUERY_RESOURCES_REQUIREMENTS,
	QUERY_DEVICE_TEXT,
	FILTER_RESOURCE_REQUIREMENTS,

	READ_CONFIG = 0x0f,
	WRITE_CONFIG,
	EJECT,
	SET_LOCK,
	QUERY_ID,
	QUERY_PNP_DEVICE_STATE,
	QUERY_BUS_INFORMATION,
	DEVICE_USAGE_NOTIFICATION,
	SURPRISE_REMOVE,

	// Power

	WAIT_WAKE = 0x00,
	POWER_SEQUENCE = 0x01,
	SET_POWER = 0x02,
	QUERY_POWER,

	// WMI

	QUERY_ALL_DATA = 0x00,
	QUERY_SINGLE_INSTANCE,
	CHANGE_SINGLE_INSTANCE,
	CHANGE_SINGLE_ITEM,
	ENABLE_EVENTS,
	DISABLE_EVENTS,
	ENABLE_COLLECTION,
	DISABLE_COLLECTION,
	REGINFO,
	EXECUTE_METHOD,
};

#pragma pack(push,1)	// 是指把原来对齐方式设置压栈，并设置新的对齐方式

struct CommonInfoHeader {
	USHORT Size;
	DataItemType Type;
	long long Time;
	ULONG ProcessId;
	ULONG ThreadId;
};

struct IrpArrivedInfo : CommonInfoHeader {
	PVOID DeviceObject;
	PVOID DriverObject;
	PVOID Irp;
	IrpMajorCode MajorFunction;
	IrpMinorCode MinorFunction;
	UCHAR Irql;
	UCHAR _padding;
	ULONG DataSize;
	union {
		struct {
			ULONG IoControlCode;
			ULONG InputBufferLength;
			ULONG OutputBufferLength;
		}DeviceIoControl;
		struct {
			USHORT FileAttributes;
			USHORT ShareAccess;
		}Create;
		struct {
			ULONG Length;
			long long Offset;
		}Read;
		struct {
			ULONG Length;
			long long Offset;
		}Write;
	};
};

struct IrpCompletedInfo :CommonInfoHeader {
	PVOID Irp;
	long Status;
	ULONG_PTR Information;
	ULONG DataSize;
};

#pragma pack(pop)	// 恢复对齐状态