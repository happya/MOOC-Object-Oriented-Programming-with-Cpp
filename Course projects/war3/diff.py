
name_in = "datapub2"
name_out="my_out" 
i=0 #行数
with open(str(name_in) + ".out", "r") as std_ans:
    with open(str(name_out) + ".out", "r") as my_ans:
        for s, t in zip(std_ans, my_ans):
            s = s.rstrip()
            t = t.rstrip()
            i = i+1
            if s != t:
                print()
                print(i,": answer:", s)
                print(i,": my    :", t)
                print()
print("down!")
