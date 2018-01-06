__author__ = 'ashwani'
from random import randrange
from random import uniform
from math import sqrt
from copy import deepcopy

#li=[]
n=9
m=(int)(sqrt(n))
li=[]
bigB=[]
fixed=[]
bolB=[]
master=[]

rescue=[]
hathi=[]
tappu=[]
dadaji=[]


unfi=[]
fi=[]
there=[]
notThere=[]
stupidc=[]
hashed=[]
instances=[]



class populate:
    def __init__(self):
        self.list=deepcopy(li)
        self.fitness=0
        #self.fixed=fixed

    def list(self):
        return self.list



    def random(self):

        for i in range(n):
            #n=len(subList)
            subList=self.list[i]

            del rescue[:]
            for j in range(n):
                if fixed[i][j]==1:
                    rescue.append( subList[j] )

            #print rescue
            for j in range(n):
                if fixed[i][j]==0:
                    dummy=randrange(1,10)
                    while True:
                        if dummy not in rescue:
                            rescue.append(dummy)
                            break
                        else:
                            dummy=randrange(1,10)

                    subList[j]=dummy
            #print self.list


    def fitty(self):
        rowf=0
        colf=0
        subf=0

        for i in range(1,n+1):
            for j in range(1,n):
                for l in range(j+1,n+1):
                    rowf+=self.fit(i,j,i,l)

        for j in range(1,n+1):
            for i in range(1,n):
                for l in range(i+1,n+1):
                    colf+=self.fit(i,j,l,j)


        for i in range(1,n+1):
            for q in range(1,m+1):

                for j in range( 1+(q-1)*m,n+1 ):
                    for l in range( j+1,q*m +1):
                        subf+=self.fit(i,j,i,l)

                for r in range( 1+(q-1)*m,q*m +1):
                    jethia=i%m
                    if jethia==0 and (i/m)>=1:
                        continue
                    else:
                        for k in range(i+1,i+m-(i%m)+1):
                            for s in range(1+(q-1)*m,q*m+1):
                                subf+=self.fit(i,r,k,s)

        self.fitness = rowf+colf+subf




    def fit(self,i,j,k,l):
        subList1=self.list[i-1]
        subList2=self.list[k-1]
        if subList1[j-1]==subList2[l-1]:
            return 0
        else:
            return 1


    def cross(self,other):
        for i in range(n):
            if i%2==0:
                #popat=uniform(0,1)
                #if popat<=0.8:
                self.list[i],other.list[i]=other.list[i],self.list[i]


    def mutate(self):

        # for s in range(n):
        #     for t in range(n):
        #         if fixed[s][t]==0:
        #             lal=uniform(0,1)
        #             if lal<=0.2:
        for i in range(n):
            lal=uniform(0,1)
            if lal<=0.5:
                while True:
                    #i=randrange(0,9)
                    j=randrange(0,9)
                    k=randrange(0,9)

                    if fixed[i][j]==0 and fixed[i][k]==0:
                        self.list[i][j],self.list[i][k]=self.list[i][k],self.list[i][j]
                        break


    def remColRep(self):
        for i in range(n):
            print i
            count=0
            del hathi[:]

            #del tappu[:]
            #del dadaji[:]

            #print 'hey'


            #print 'shhhhhhhhhhhhhhhhhhhhhhhhhhhhhuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuut upppppppppppppppp'
            while True:
                count=0
                del hathi[:]

                for j in range(n):
                    if fixed[j][i]==1:
                        hathi.append( self.list[j][i] )
                        count+=1
                    else:


                        if self.list[j][i] in hathi:
                            #taking a variable here would be a much better idea
                            temp=j
                            #tappu.append( list[j][i] )
                            #dadaji.append(j)
                        else:
                            hathi.append( self.list[j][i] )
                            count+=1


                print 'halllllllo'
                print hathi
                if count==n:
                    break


                dandia=0
                for j in range(1,n+1):
                    if j in hathi:
                        continue
                    else:
                        print 'here i am'
                        for theta in range(n):
                            if fixed[temp][theta]==1:
                                continue
                            elif self.list[temp][theta]==j and fixed[temp][theta]==0:

                                self.list[temp][theta],self.list[temp][i]=self.list[temp][i],self.list[temp][theta]
                                count+=1
                                dandia=1
                                break

                        if dandia==1:
                            break



                if count==n:
                    break


                print(count)
                print temp
                print self.list
                #self.list[temp][i]=star
                #print self.list

        #print 'down'



    def remColRep1(self):
        del fi[:]
        del unfi[:]
        del there[:]
        del notThere[:]

        for j in range(n):
            for i in range(n):
                if fixed[i][j]==1:
                    fi.append( (self.list[i][j],i) )
                    there.append(self.list[i][j])

            for i in range(n):
                if fixed[i][j]==0:
                    unfi.append( (self.list[i][j],i) )
                    if i in there:
                        continue
                    else:
                        there.append(i)

            for i in range(1,10):
                if i in there:
                    continue
                else:
                    notThere.append(i)

            del stupidc[:]     ###   (changed to a better one)  :)

            for i in range( len(unfi) ):
                if unfi[i][0] in fi:
                    stupidc.append( unfi[i] )



            count1=len(stupidc)

            while count1>0:
                m1=len(notThere)-1
                #dummy=notThere[m1]
                flag=0

                pos=stupidc[count1-1]
                #dibba=len(unfi)-1
                while True:

                    for dhakkan in range(10):
                        if notThere[m1]==self.list[ pos[1] ][dhakkan] and dhakkan!=j:
                            if fixed[ pos[1] ][dhakkan]==0:
                                self.list[pos[1]][dhakkan],self.list[pos[1]][j] = self.list[pos[1]][j],self.list[pos[1]][dhakkan]

                                stupidc.pop()
                                notThere.pop()
                                flag=1
                                break
                            else:
                                break

                    if flag==0 and m1>0:
                        m1=m1-1
                    else:
                        break

                count1=count1-1


            #appending unfi

            del unfi[:]
            for i in range(n):
                if fixed[i][j]==0 :
                    unfi.append( (self.list[i][j],i) )

            if len(notThere)==0:
                continue

            del hashed[:]

            for i in range(n+1):
                hashed.append(0)

            for i in range(n):
                hashed[ self.list[i][j] ] +=1

            for i in range(1,10):
                del instances[:]
                if hashed[i]>1:

                    for k in range( len(unfi) ):
                        if i==unfi[k][0]:
                            instances.append(unfi[k])

                    while hashed[i]>1:


                        count1=len(instances)
                        pos=instances[count1-1]
                        flag=0

                        m1=len(notThere)-1
                        while True:

                            for dhakkan in range(10):
                                if notThere[m1]==self.list[ pos[1] ][dhakkan] and dhakkan!=j:
                                    if fixed[ pos[1] ][dhakkan]==0:
                                        self.list[pos[1]][dhakkan],self.list[pos[1]][j] = self.list[pos[1]][j],self.list[pos[1]][dhakkan]

                                        instances.pop()
                                        notThere.pop()
                                        flag=1
                                        hashed[i]-=1
                                        break
                                    else:
                                        break

                                if flag==0 and m1>0:
                                    m1=m1-1
                                else:
                                    break





def sudoku():

    text_file = open("Easy.txt", "r")
    lines= [ int(x) for x in text_file.read().split()  ];
    text_file.close()


    for i in range(len(lines)):
        dabba=i/n
        if dabba%n==0:
            li.append([])

        li[dabba].append( lines[i] )

    k=0
    for subList in li:
        fixed.append([])
        for i in range(n):
            if subList[i]!=0:
                fixed[k].append(1)
            else:
                fixed[k].append(0)
        k+=1

    #print fixed



if __name__=="__main__":
    sudoku()
    reflex=0
    flag=0

    for i in range( 10*n ):
        bigB.append([])
        bigB[i]=populate()
        bigB[i].random()
        bigB[i].remColRep1()                    #I DOUBT THIS THING

        bigB[i].fitty()

        if bigB[i].fitness == 972:
            flag=2
            reflex=i
            break
        #print bigB[i].list
        #print bigB[i].fixed
        #print bigB[i].fitness




    count=0
    #flag=0

    while count<10000:

        #test
        #for i in range(10*n):
        #    print bigB[i].list

        bolB=deepcopy(bigB)
        #bigB[8].cross(bigB[9])
        #print bigB[8].list
        #print bigB[9].list


        #time for cross-over
        for i in range(10*n):
            if i%2==0:
                popat=uniform(0,1)
                if popat<=0.8:
                    bolB[i].cross(bolB[i+1])

            bolB[i].remColRep1()
        #for i in range(10):
        #    print bolB[i].list

        #print bolB[0].list
        for i in range(10*n):
            bolB[i].mutate()

            bolB[i].remColRep1()
            bolB[i].fitty()

            if bolB[i].fitness == 972:
                flag=3
                reflex=i
                break

            #print bolB[i].fitness,

        #test
        #print
        #print " time for bolb  "
        #print

        ##for i in range(10*n):
        #    print bolB[i].list

        #print ' '
        #print ' '

        master=bigB+bolB

        #for i in range(2*10):
        #    print master[i].fitness,


        #print ' '

        #time for insertion sort

        for i in range(1,2*10*n):
            j=i-1
            temp=master[i]
            while j>=0 and master[j].fitness < temp.fitness:
                master[j+1]=master[j]
                j=j-1

            master[j+1]=temp


        if master[0].fitness == 972:
            flag=1
            break
        #for i in range(2*10):
        #    print master[i].fitness,
        #print ' '

        del bigB[:]
        del bolB[:]

        #for i in range(10):
        #    print master[i].list

        for i in range(10*n):
            bigB.append(master[i])

            #seems to be not that necessary
            #print 'hey'
            bigB[i].remColRep1()
            #print 'enoooooooooooooooooooooooooooooooooooooooooughhhhhhhhhhhhhhhhhhhhhhhhhh ooffffffffffffffffffffffffffff iiiiiiiiiiiiiiiiiit!!!!!!!11'


        count+=1
        print "generation " + str(count)
        del master[:]

        print bigB[0].fitness




        #remove the colum repetition at this stage


        #print bigB

    if flag==1:
        print "yes found"
        print master[0].list
        print flag,count
    elif flag==2:
        print "yes found"
        print bigB[reflex].list
        print flag,count
    elif flag==3:
        print "yes found"
        print bolB[reflex].list
        print flag,count
    else:
        print "solution not found"
