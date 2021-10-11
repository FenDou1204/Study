import matplotlib.pyplot as plt


#plot huan shu hou
values = [1, 2, 3, 4, 5]
squares = [1, 4, 9, 16, 25]
plt.plot(values, squares, linewidth=5)      #xian de cu xi

plt.title("Square Numbers", fontsize=24)    #sheng cheng biao de ming cheng
plt.xlabel("Value", fontsize=24)            #x zhou de shu ju ming cheng
plt.ylabel("Squares", fontsize=24)          #y zhou de shu ju ming cheng

plt.tick_params(axis='both', labelsize=14)
plt.show()
