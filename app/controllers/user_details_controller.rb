class UserDetailsController < ApplicationController
    before_action :set_ud, only: [:edit, :update, :show, :destroy]
    def new
        @ud=UserDetail.new
    end
    def index
        @ud=UserDetail.all
    end

    def show
    end

    def edit
    end
    
    def update
        if @ud.update(ud_params)
          flash[:notice] = "Your account information was successfully updated"
          redirect_to @ud
        else
          render 'edit',status: :unprocessable_entity
        end
    end
   
    def create
        @ud = UserDetail.new(ud_params)
        if @ud.save
            UserDetailMailer.booking_confirmation(@ud).deliver_later
            flash[:notice] = "successfully applied"
            redirect_to @ud
        else
            render 'new', status: :unprocessable_entity
        end
    end
    def destroy
      @ud.destroy
      redirect_to user_details_path
    end 

      def ud_params
        params.require(:user_detail).permit(:client_name, :email ,:car_color ,:car_number, :in_time, :out_time, :price, :floor_id)
      end
  
      def set_ud
        @ud = UserDetail.find(params[:id])

        rescue ActiveRecord::RecordNotFound => error
        redirect_to user_details_path
        flash[:notice] = error
      end

end

