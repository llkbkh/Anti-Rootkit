#pragma once

#include "AppCommandBase.h"

struct DeleteKeyCommand :public RegAppCommandBase<DeleteKeyCommand> {
	DeleteKeyCommand(PCWSTR path, PCWSTR name, AppCommandCallback<DeleteKeyCommand> cb = nullptr);

	bool Execute() override;
	bool Undo() override;

private:
	CString _savePath;
};