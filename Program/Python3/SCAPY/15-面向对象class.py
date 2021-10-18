'''
本来想以宠物来当成一个类来进行自己学习，每个人的宠物各不相同，所以它可以包含
宠物的种类，宠物的名字，宠物的年龄，宠物的性别等通用行为，然后根据需要赋予
每个对象独特的个性。

根据类来创建对象称为实例化。
'''
class Dog():
    '''一个小狗的类'''
    def __init__(self, name, age):
        self.name = name        #属性
        self.age = age

    def sit(self):              #方法
        print(self.name.title() + " is now sitting.")

    def roll_over(self):
        print(self.name.title() + " rolled over!")



my_dog = Dog('duoduo', 8)
print("Dog's name is %s"%my_dog.name) #访问属性
my_dog.sit()
my_dog.roll_over()
