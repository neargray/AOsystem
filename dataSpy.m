close all;clc;
% 先要运行PreCalc4AOSys_v10.m

%%
% tool-1
% 用于看某一范围数据个数和索引
close all;clc;
range=19; % 查看范围
counter=0;
for row=1:610
    for col=1:140
        if (A(row,col) + 0.5360<0.0001)
            row;
            col;
            A(row,col);
            counter=counter+1;
        end        
    end
end
counter

%%
close all;clc;
% 直方图用于看数据分布
figure
histogram(pinv(A_temp),640)

%%
% 显示脱靶量的图像
for index=1:140
    figure(index);
    surf(Devi_X_Pupil{index});
end

%%


