module CheckRole
    extend ActiveSupport::Concern

    private

    def check_user
      return unless current_user.admin == false
      flash[:alert] = "You can't open this"
      redirect_to root_path
    end
end 