import cv2
import numpy as np

class CalibrationBoard():
    img=[]
    img_RT=[]
    def create_concentric_circles(self,inner_radius=50,outer_radius=150,isfill=True,center_mark=0,thickness=1)->list:
        """
        生成圆环标定图
        inner_radius(int): 内圆半径.
        outer_radius(int): 内圆半径.
        isfill(bool):是否填充圆环
        expend(int): 图像在外圆基础上扩展像素,决定图像大小.
        center_mark(int): 标出圆心"+"大小,center_mark=0时默认不标出.
        thickness(int): 线条宽度.

        Returns:
        bool: Description of the return value.
        """
        size=[outer_radius*2+outer_radius//4,outer_radius*2+outer_radius//4]
        center=[item // 2 for item in size]

        # 初始化图像
        self.img = np.zeros(size, np.uint8)
        self.img.fill(255)
        if  isfill:
            # 画同心圆
            cv2.circle(self.img,center, outer_radius, (0), thickness = -1)
            cv2.circle(self.img,center, inner_radius, (255), thickness = -1)
        else:

            # 画同心圆
            cv2.circle(self.img,center, inner_radius, (0), thickness = thickness)
            cv2.circle(self.img,center, outer_radius, (0), thickness = thickness)

        # 标注加号
        if center_mark>0:
            cv2.line(self.img,[center[0]-center_mark,center[1]],[center[0]+center_mark,center[1]], (0), thickness = thickness)
            cv2.line(self.img,[center[0],center[1]-center_mark],[center[0],center[1]+center_mark], (0), thickness = thickness)
        # 显示结果
        # cv2.imshow("Original", img)
        # cv2.waitKey(0)
        return self.img

    def create_checker_board(self,width=6,height=8,edge=100)->np.mat:
        """
        width(int): 棋盘格横向点数.
        height(int): 棋盘格纵向点数.
        edge(int): 棋盘格单格边长.
        Returns:
        bool: Description of the return value.
        """
        self.img = np.zeros(((height+1)*edge,(width+1)*edge))
        black_block = np.full((edge,edge),255)
        for row in range(height+1):
            for col in range(width+1):
                if (row+col)%2==0:
                    row_begin = row*edge
                    row_end = row_begin+edge
                    col_begin = col*edge
                    col_end = col_begin+edge
                    self.img[row_begin:row_end,col_begin:col_end] = black_block
        self.img=cv2.copyMakeBorder(self.img,edge//4,edge//4,edge//4,edge//4,cv2.BORDER_CONSTANT,value=[255])

        # 显示结果
        # cv2.imwrite("checker_board.jpg",img)
        # cv2.imshow("checker_board",img)
        # cv2.waitKey(0)
        return self.img

    def create_BMW_logo(self,radius=200):
        size=[radius*2,radius*2]
            # 初始化图像
        self.img = np.zeros(size, np.uint8)
        cv2.circle(self.img,[radius,radius], radius, (0), thickness = -1)
        # self.img.fill(255)
        cv2.circle(self.img,[radius,radius], radius, (0), thickness = -1)
        self.img[0:radius,0:radius] =255
        self.img[radius:2*radius,radius:2*radius] =255
        self.img=cv2.copyMakeBorder(self.img,radius//4,radius//4,radius//4,radius//4,cv2.BORDER_CONSTANT,value=[255])
        # cv2.imwrite("checker_board.jpg",img)
        cv2.imshow("Original", self.img)
        cv2.waitKey(0)

    def create_single_corner(self,radius=200):
        size=[radius*2,radius*2]
        # 初始化图像
        self.img = np.zeros(size, np.uint8)
        self.img[0:radius,0:radius] =255
        self.img[radius:2*radius,radius:2*radius] =255
        # img=cv2.copyMakeBorder(img,radius//4,radius//4,radius//4,radius//4,cv2.BORDER_CONSTANT,value=[255])
        # cv2.imwrite("checker_board.jpg",img)
        cv2.imshow("Original", self.img)
        cv2.waitKey(0)

    def transform(self,theta_x=0.0,theta_y=0.0,theta_z=0.0,move_x=0.0,move_y=0.0):
        # 绕坐标轴x,y,z旋转角度和平移的参数
        R_vec = np.array([[theta_x], [theta_y], [theta_z]])

        # cv2.Rodrigues函数有两个功能: 1、输入旋转向量 返回旋转矩阵R;2、输入旋转矩阵R返回旋转向量和雅克比矩阵。
        R = cv2.Rodrigues(R_vec)[0]
        print(R)
        T_vec = np.array([move_x, move_y,0])

        H = np.hstack((R, T_vec.reshape(3,1)))
        # H = np.vstack((H, [0,0,0,1]))
        # print(H)

        # 计算变换后的结果
        self.img_RT = cv2.warpPerspective(self.img, R, (500, 500))
        return R


if __name__=='__main__':
    cb=CalibrationBoard()
    cb.create_BMW_logo()
    cb.create_concentric_circles(center_mark=10,thickness=1)
    R=cb.transform(theta_x = 0.005,theta_y = 0.0005)

    # # 显示结果
    # cv2.imshow("Perspective Transformation", cb.img_RT)
    # cv2.imwrite("concentric_circles4.jpg",cb.img_RT)
    # cv2.waitKey(0)

