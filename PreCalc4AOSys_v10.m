clear all;close all;clc;


%-------------------------拼接矩阵----------------------------------%

% 输入数据所在的文件夹
filepath='D:\externLib\AOS\Output\PreCalc\in\';

% 将传递函数的X脱靶量读入，并将所有响应函数存入cell中
Devi_X=cell(144,1);  % 保存全部的X方向脱靶量
for index=0:143
   load([filepath 'XDevi_' num2str(index) '.txt']);
   Devi_X{index+1}=eval(strcat('XDevi_',num2str(index)));
end

% 将传递函数的Y脱靶量读入，并将所有响应函数存入cell中
Devi_Y=cell(144,1);  % 保存Y方向脱靶量
for index=0:143
   load([filepath 'YDevi_' num2str(index) '.txt']);
   Devi_Y{index+1}=eval(strcat('YDevi_',num2str(index)));
end


% 计算光瞳，输出有效点个数，有效点的索引位置
x_DM=linspace(-2.1,2.1,29);
y_DM=x_DM;
eff_picked=cell(841,1); % 保存有效点的索引位置
eff_counter=0; % 保存有效点的个数
pupil_DM=zeros(29,29);
for row=1:29   
    for col=1:29
        if sqrt(x_DM(row)^2+y_DM(col)^2) < 1.5
            
            eff_counter=eff_counter+1; % 有效子孔径点数+1
            pupil_DM(row,col)=1; % 1.5mm
            eff_picked{eff_counter}(1)=row; % 储存行信息
            eff_picked{eff_counter}(2)=col; % 储存列信息
            
        end
    end
end


% 给脱靶量加上光瞳
Devi_X_Pupil=cell(144,1);
Devi_Y_Pupil=cell(144,1);  % 保存Y方向脱靶量
for index=1:144
    
    Devi_X_Pupil{index}=Devi_X{index}.*pupil_DM;
    Devi_Y_Pupil{index}=Devi_Y{index}.*pupil_DM;
    
end


% 提取有效点，组合为矩阵A
A=zeros(1,144); % 拼接前的初始化
for subaperture_index=1:eff_counter   % 遍历所有有效点
    
    % 获取当前循环有效点的行列索引号
    row_ergodic=eff_picked{subaperture_index}(1);
    col_ergodic=eff_picked{subaperture_index}(2);
    
    % 沿第二个维度（横向，行方向）拼接得到行向量，维度为2x140,2行，140列
    A_partial=[0;0]; % 拼接前的初始化
    for impulse_index=1:144
        
        A_partial_xy=[
            Devi_X_Pupil{impulse_index}(row_ergodic,col_ergodic);
            Devi_Y_Pupil{impulse_index}(row_ergodic,col_ergodic)
            ];
        
        % 这里注意拼接的顺序，要从左到右拼接
        A_partial=cat(2,A_partial,A_partial_xy); % 不断的拼接        
        
    end % 循环结束，得到A_partial为2x141的矩阵
    A_partial=A_partial(:,2:145); % 删掉初始化的一列，位于最前列（第一列）
    
    % 将2x140的矩阵，沿第一个维度（纵向，列方向）拼接得到需要的矩阵A
    A=cat(1,A,A_partial);
    
end % 循环结束，得到A为(2*eff_counter+1)x140的矩阵

% 最终得到拼接后的系数矩阵！下面再求逆！
A=A(2:2*eff_counter+1,:); % 删掉初始化的第一行，位于最前行（第一行）


%-------------------------求逆----------------------------------%



% A是一个矩形阵,A_temp是一个方阵
A_temp=A'*A;  % A'是A的厄米矩阵（自共轭矩阵）, A.' 是非共轭转置
% if det(A_temp)==0  
%     lsqA=pinv(A_temp)*A'; % 如果A_temp为奇异矩阵，求伪逆
% else
%     lsqA=inv(A_temp)*A';  % 如果A_temp为非奇异矩阵，求逆
% end
lsqA=pinv(A_temp)*A';

%-------------------------输出至文本----------------------------------%
% 将lsqA写入文本
fid=fopen('D:\externLib\AOS\Output\PreCalc\out\lsqA.txt','w');
for row=1:size(lsqA,1)
    for col=1:size(lsqA,2)
        fprintf(fid,'%10f  ',lsqA(row,col));      
    end
    fprintf(fid,'\n');
end

% 将有效子孔径索引信息写入文件
fid=fopen('D:\externLib\AOS\Output\PreCalc\out\eff_picked.txt','w');
for counter=1:eff_counter   % 遍历每个有效子孔径
    
    fprintf(fid,'%10f\t',eff_picked{counter,1}(1));  % 某个有效子孔径的row信息
    fprintf(fid,'%10f\t',eff_picked{counter,1}(2));  % 某个有效子孔径的col信息
    fprintf(fid,'\n');
    
end




