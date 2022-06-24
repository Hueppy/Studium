import inspect
import selfreproduce

if __name__ == "__main__":
#    f = open("selfreproduce.py", mode="r")
#    print(f.read())
#    f.close()

    print(inspect.getsource(selfreproduce))