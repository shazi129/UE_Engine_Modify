#coding:utf-8

import os
import subprocess


src_dir = "H:/GitHub/UE_Engine_Modify/Engine"
dst_dir = "H:/UnrealEngine/Engine/"

def GetAllFile(dirPath):
    ret = []
    allsub = os.listdir(dirPath)
    for sub in allsub:
        subPath = "%s/%s" % (dirPath, sub)
        if os.path.isfile(subPath):
            ret.append(subPath)
        if os.path.isdir(subPath):
            ret.extend(GetAllFile(subPath))
    return ret

def execute_cmd(cmd, encoding=""):

        print(cmd)

        pipe = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

        #实时读出一些数据
        while pipe.poll() == None:
            line_byte = pipe.stdout.readline()
            print(bytes.decode(line_byte, encoding), end="");

        out = pipe.stdout.read()
        if len(out) > 0:
           print(bytes.decode(out, encoding), end="");

        err = pipe.stderr.read()
        if len(err) > 0:
            print("execute cmd error:", bytes.decode(err, encoding))

if __name__ == "__main__":
	allFile = GetAllFile(src_dir)
	for file in allFile:
		engineFile = "%s%s" % (dst_dir, file.lstrip(src_dir))

		#删除引擎中的文件
		if os.path.exists(engineFile):
			os.remove(engineFile)

		#如果目录不存在，需要创建目录
		dirName, fileName = os.path.split(engineFile)
		if not os.path.exists(dirName):
			os.makedirs(dirName)
		
		#运行生成硬链接的命令
		cmd = "mklink /H %s %s" %(engineFile.replace('/', '\\'), file.replace('/', '\\'))
		execute_cmd(cmd, "gbk")