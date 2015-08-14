clear all;close all;clc;


%-------------------------ƴ�Ӿ���----------------------------------%

% �����������ڵ��ļ���
filepath='D:\externLib\AOS\Output\PreCalc\in\';

% �����ݺ�����X�Ѱ������룬����������Ӧ��������cell��
Devi_X=cell(144,1);  % ����ȫ����X�����Ѱ���
for index=0:143
   load([filepath 'XDevi_' num2str(index) '.txt']);
   Devi_X{index+1}=eval(strcat('XDevi_',num2str(index)));
end

% �����ݺ�����Y�Ѱ������룬����������Ӧ��������cell��
Devi_Y=cell(144,1);  % ����Y�����Ѱ���
for index=0:143
   load([filepath 'YDevi_' num2str(index) '.txt']);
   Devi_Y{index+1}=eval(strcat('YDevi_',num2str(index)));
end


% �����ͫ�������Ч���������Ч�������λ��
x_DM=linspace(-2.1,2.1,29);
y_DM=x_DM;
eff_picked=cell(841,1); % ������Ч�������λ��
eff_counter=0; % ������Ч��ĸ���
pupil_DM=zeros(29,29);
for row=1:29   
    for col=1:29
        if sqrt(x_DM(row)^2+y_DM(col)^2) < 1.5
            
            eff_counter=eff_counter+1; % ��Ч�ӿ׾�����+1
            pupil_DM(row,col)=1; % 1.5mm
            eff_picked{eff_counter}(1)=row; % ��������Ϣ
            eff_picked{eff_counter}(2)=col; % ��������Ϣ
            
        end
    end
end


% ���Ѱ������Ϲ�ͫ
Devi_X_Pupil=cell(144,1);
Devi_Y_Pupil=cell(144,1);  % ����Y�����Ѱ���
for index=1:144
    
    Devi_X_Pupil{index}=Devi_X{index}.*pupil_DM;
    Devi_Y_Pupil{index}=Devi_Y{index}.*pupil_DM;
    
end


% ��ȡ��Ч�㣬���Ϊ����A
A=zeros(1,144); % ƴ��ǰ�ĳ�ʼ��
for subaperture_index=1:eff_counter   % ����������Ч��
    
    % ��ȡ��ǰѭ����Ч�������������
    row_ergodic=eff_picked{subaperture_index}(1);
    col_ergodic=eff_picked{subaperture_index}(2);
    
    % �صڶ���ά�ȣ������з���ƴ�ӵõ���������ά��Ϊ2x140,2�У�140��
    A_partial=[0;0]; % ƴ��ǰ�ĳ�ʼ��
    for impulse_index=1:144
        
        A_partial_xy=[
            Devi_X_Pupil{impulse_index}(row_ergodic,col_ergodic);
            Devi_Y_Pupil{impulse_index}(row_ergodic,col_ergodic)
            ];
        
        % ����ע��ƴ�ӵ�˳��Ҫ������ƴ��
        A_partial=cat(2,A_partial,A_partial_xy); % ���ϵ�ƴ��        
        
    end % ѭ���������õ�A_partialΪ2x141�ľ���
    A_partial=A_partial(:,2:145); % ɾ����ʼ����һ�У�λ����ǰ�У���һ�У�
    
    % ��2x140�ľ����ص�һ��ά�ȣ������з���ƴ�ӵõ���Ҫ�ľ���A
    A=cat(1,A,A_partial);
    
end % ѭ���������õ�AΪ(2*eff_counter+1)x140�ľ���

% ���յõ�ƴ�Ӻ��ϵ���������������棡
A=A(2:2*eff_counter+1,:); % ɾ����ʼ���ĵ�һ�У�λ����ǰ�У���һ�У�


%-------------------------����----------------------------------%



% A��һ��������,A_temp��һ������
A_temp=A'*A;  % A'��A�Ķ��׾����Թ������, A.' �Ƿǹ���ת��
% if det(A_temp)==0  
%     lsqA=pinv(A_temp)*A'; % ���A_tempΪ���������α��
% else
%     lsqA=inv(A_temp)*A';  % ���A_tempΪ�������������
% end
lsqA=pinv(A_temp)*A';

%-------------------------������ı�----------------------------------%
% ��lsqAд���ı�
fid=fopen('D:\externLib\AOS\Output\PreCalc\out\lsqA.txt','w');
for row=1:size(lsqA,1)
    for col=1:size(lsqA,2)
        fprintf(fid,'%10f  ',lsqA(row,col));      
    end
    fprintf(fid,'\n');
end

% ����Ч�ӿ׾�������Ϣд���ļ�
fid=fopen('D:\externLib\AOS\Output\PreCalc\out\eff_picked.txt','w');
for counter=1:eff_counter   % ����ÿ����Ч�ӿ׾�
    
    fprintf(fid,'%10f\t',eff_picked{counter,1}(1));  % ĳ����Ч�ӿ׾���row��Ϣ
    fprintf(fid,'%10f\t',eff_picked{counter,1}(2));  % ĳ����Ч�ӿ׾���col��Ϣ
    fprintf(fid,'\n');
    
end




