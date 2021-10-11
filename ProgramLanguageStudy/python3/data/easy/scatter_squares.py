import matplotlib.pyplot as plt

x_values = list(range(1, 1001))
y_values = [x**2 for x in x_values]

plt.title("Square Numbers", fontsize=24)
plt.xlabel("Value", fontsize=14)
plt.ylabel("Square of Value", fontsize=14)
plt.tick_params(axis='both', which='major', labelsize=14)

#plt.scatter(x_values, y_values, s=1)
# c daibiao yan se   keyi shi yige () yuan zu
plt.scatter(x_values, y_values, c='yellow', edgecolor='none',s=1)
# yan se jian bian
plt.scatter(x_values, y_values, c=y_values,
            cmap=plt.cm.Blues, edgecolor='none', s=1)
plt.axis([0, 1100, 0, 1100000])

plt.show()
#plt.savefig('x*x', bbox_inches='tight')
