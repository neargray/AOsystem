close all;clc;
% ��Ҫ����PreCalc4AOSys_v10.m

%%
% tool-1
% ���ڿ�ĳһ��Χ���ݸ���������
close all;clc;
range=19; % �鿴��Χ
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
% ֱ��ͼ���ڿ����ݷֲ�
figure
histogram(pinv(A_temp),640)

%%
% ��ʾ�Ѱ�����ͼ��
for index=1:140
    figure(index);
    surf(Devi_X_Pupil{index});
end

%%


