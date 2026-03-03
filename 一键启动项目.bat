@echo off
chcp 65001 > nul

echo ===============================
echo UE项目C++代码自动编译脚本
echo ===============================

:: 项目配置
setlocal enabledelayedexpansion

:: ========== UE 版本配置 ==========
:: 设置要查找的 Unreal Engine 版本号 (例如：5.7, 5.6, 5.5 等)
:: 留空则自动查找默认版本
set "UE_VERSION=5.7"
:: ================================




:: 自动获取项目根目录（脚本所在目录）
set "PROJECT_PATH=%~dp0"
:: 移除末尾的反斜杠
if "%PROJECT_PATH:~-1%"=="\" set "PROJECT_PATH=%PROJECT_PATH:~0,-1%"

echo [调试] 脚本所在目录: %~dp0
echo [调试] 项目根目录: %PROJECT_PATH%
echo [调试] 当前工作目录: %CD%

:: 自动查找.uproject文件
echo [信息] 正在查找.uproject文件...
echo [信息] 搜索路径: %PROJECT_PATH%

for %%f in ("%PROJECT_PATH%\*.uproject") do (
    echo [信息] 找到.uproject文件: %%f
    set "UPROJECT_FILE=%%f"
    set "PROJECT_NAME=%%~nf"
    goto found_uproject
)

echo [错误] 未找到.uproject文件，请确保脚本在项目根目录
pause
exit /b 1

:found_uproject
echo [信息] 项目名称: %PROJECT_NAME%
echo [信息] 项目路径: %PROJECT_PATH%
echo [信息] UProject文件: %UPROJECT_FILE%

:: 从注册表查找UnrealBuildTool路径
echo [信息] 正在从注册表查找Unreal Engine 安装路径...
if defined UE_VERSION (
    echo [信息] 指定版本：%UE_VERSION%
)

:: 尝试从多个可能的注册表位置查找
set "UE_INSTALL_PATH="

:: 如果指定了版本，优先查找指定版本的 InstalledDirectory
if defined UE_VERSION (
    for /f "tokens=2*" %%a in ('reg query "HKEY_LOCAL_MACHINE\SOFTWARE\EpicGames\Unreal Engine\%UE_VERSION%" /v "InstalledDirectory" 2^>nul') do (
        if not defined UE_INSTALL_PATH set "UE_INSTALL_PATH=%%b"
    )
)

:: 如果没找到或未指定版本，尝试 Epic Games 启动器的注册表项（当前用户）
if not defined UE_INSTALL_PATH (
    for /f "tokens=2*" %%a in ('reg query "HKEY_CURRENT_USER\Software\EpicGames\Unreal Engine" /v "InstallPath" 2^>nul') do (
        if not defined UE_INSTALL_PATH set "UE_INSTALL_PATH=%%b"
    )
)

:: 如果还是没找到，尝试本地机器的通用位置
if not defined UE_INSTALL_PATH (
    for /f "tokens=2*" %%a in ('reg query "HKEY_LOCAL_MACHINE\SOFTWARE\EpicGames\Unreal Engine" /v "InstallPath" 2^>nul') do (
        if not defined UE_INSTALL_PATH set "UE_INSTALL_PATH=%%b"
    )
)

:: 如果仍然未找到，报错提示
if not defined UE_INSTALL_PATH (
    echo [警告] 未从注册表找到 Unreal Engine 安装路径
    if defined UE_VERSION (
        echo [提示] 请检查注册表 HKEY_LOCAL_MACHINE\SOFTWARE\EpicGames\Unreal Engine\%UE_VERSION% 是否存在
    )
    echo [提示] 或手动设置 UE_INSTALL_PATH 环境变量
    pause
    exit /b 1
)
echo [信息] UE_INSTALL_PATH: %UE_INSTALL_PATH%

:: ... existing code ...



set "UBT_PATH=%UE_INSTALL_PATH%\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe"
echo [信息] UE安装路径: %UE_INSTALL_PATH%
echo [信息] UnrealBuildTool路径: %UBT_PATH%

:: 检查必要文件
if not exist "%UBT_PATH%" (
    echo [错误] 未找到UnrealBuildTool.exe，请检查UE安装路径是否正确
    pause
    exit /b 1
)

if not exist "%UPROJECT_FILE%" (
    echo [错误] 未找到项目文件，请检查项目路径是否正确
    pause
    exit /b 1
)

:: 检查Git是否可用
@REM echo [信息] 检查Git是否可用...
@REM git --version > nul 2>&1
@REM if %errorlevel% neq 0 (
@REM     echo [警告] Git未安装或未添加到环境变量
@REM     echo [提示] 将跳过Git拉取步骤
@REM     goto skip_git
@REM )

:: Git拉取最新代码
@REM echo [执行] 正在从Git拉取最新代码...
@REM git pull
@REM if %errorlevel% neq 0 (
@REM     echo [警告] git pull 可能有冲突或失败
@REM     echo [提示] 请手动解决冲突后重试
@REM     pause
@REM     exit /b 1
@REM )
@REM echo [成功] Git拉取完成

:skip_git
:: 编译项目
echo [执行] 正在编译C++代码...
"%UBT_PATH%" %PROJECT_NAME% Win64 Development -Project="%UPROJECT_FILE%" -TargetType=Editor -Progress

if %errorlevel% equ 0 (
    echo [成功] C++代码编译完成
) else (
    echo [错误] 编译失败，请检查错误信息
    pause
    exit /b 1
)

start "" "%UPROJECT_FILE%" 

echo [完成] 所有操作已完成
exit /b 0